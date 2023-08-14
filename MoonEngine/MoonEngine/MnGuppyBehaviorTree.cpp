#include "MnGuppyBehaviorTree.h"

#include "MnDropCoin.h"
#include "MnMove.h"
#include "MnPlayAnimaion.h"
#include "MnIsTurn.h"
#include "MnGuppyTurn.h"

#include "MnAnimation.h"
#include "MnGameObject.h"
#include "MnRandomSelector.h"

#include "MnAddHungryStack.h"
#include "MnIsHungry.h"
#include "MnFindFood.h"
#include "MnMove2Food.h"
#include "MnEatFood.h"
#include "MnAddLevel.h"

#include "MnKdTree.h"

#include "playScene.h"
#include "MnFood.h"

namespace Mn
{
	GuppyBehaviorTree::GuppyBehaviorTree()
		: _Root(nullptr)
		,_Sequence(nullptr)
		,_Selector(nullptr)
		,_Inverter(nullptr)
		,_BlackBoard(nullptr)
	{
	}
	GuppyBehaviorTree::~GuppyBehaviorTree()
	{
	}
	void GuppyBehaviorTree::Initialize()
	{
		_BlackBoard = std::make_shared<BlackBoard>();

		//value
		float speed = 0.8f;
		eBehavior behavior = eBehavior::Swim;
		eFishState fishstate = eFishState::Full;
		eDir dir = eDir::Left;
		float level = 1;
		int HungryStack=0;
		UINT levelStack = 0;

		KdTree* foodtree =Mn::kdTree;


		//setData
		_BlackBoard->AddData<GameObject>(L"Guppy", GetOwner());
		_BlackBoard->AddData<KdTree>(L"Food_Tree", foodtree);


		_BlackBoard->MakeData<int>(L"HungryStack");
		_BlackBoard->SetData(L"HungryStack", HungryStack);
		_BlackBoard->MakeData<float>(L"Level");
		_BlackBoard->SetData(L"Level", level);
		_BlackBoard->MakeData<float>(L"MoveSpeed");
		_BlackBoard->SetData(L"MoveSpeed", speed);
		_BlackBoard->MakeData<UINT>(L"Level_Stack");
		_BlackBoard->SetData(L"Level_Stack", levelStack);
		
		_BlackBoard->MakeData<eBehavior>(L"Behavior");
		_BlackBoard->SetData(L"Behavior", behavior);
		_BlackBoard->MakeData<eFishState>(L"Fish_State");
		_BlackBoard->SetData(L"Fish_State", fishstate);
		_BlackBoard->MakeData<eDir>(L"Dir");
		_BlackBoard->SetData(L"Dir", dir);

		_BlackBoard->MakeData<double>(L"End");
		_BlackBoard->SetData(L"End", 0.0f);
		_BlackBoard->MakeData<bool>(L"CollisionEnter");
		_BlackBoard->MakeData<bool>(L"CollisionStay");
		_BlackBoard->MakeData<Collider2D>(L"other");


		//Hungry
		Succeeder* HungrySucceder;
		Selector* HungrySelector;
		Sequence* HungrySequence;
		AddHungryStack* addStack;
		IsHungry* isHungry;
		RepeatUntilFail* Hungryrepeat;
		Sequence* eatSequence;
		FindFood* findFood;
		
		Sequence* eatSequence_;
		Inverter* eatInverter;
		Move2Food* move2food;
		EatFood* eatfood;
		AddLevel* addlevel;

		//turn
		Succeeder* turnSucceeder;
		Sequence* turnSequence;
		IsTurn* isturn;
		GuppyTurn* guppyturn;
		
		//swim
		Sequence* swimSequence;
		DropCoin* dropCoin;
		Move* move;
		PlayAnimaion* playanima[2];
		


		_Root = new RootNode(_BlackBoard.get());
		_Root->SetTimer();
		_Sequence = _Root->setChild<Sequence>();

		HungrySucceder = _Sequence->AddChild<Succeeder>();
		HungrySequence = HungrySucceder->SetChild<Sequence>();
		addStack = HungrySequence->AddChild<AddHungryStack>();
		isHungry = HungrySequence->AddChild<IsHungry>();

		Hungryrepeat = HungrySequence->AddChild<RepeatUntilFail>();
		eatSequence = Hungryrepeat->SetChild<Sequence>();

		findFood = eatSequence->AddChild<FindFood>();
		eatInverter = eatSequence->AddChild<Inverter>();

		eatSequence_ = eatInverter->SetChild<Sequence>();
		
		move2food = eatSequence_->AddChild<Move2Food>();
		eatSequence_->AddChild<PlayAnimaion>();
		eatfood = eatSequence_->AddChild<EatFood>();
		addlevel = eatSequence_->AddChild<AddLevel>();

		turnSucceeder = _Sequence->AddChild<Succeeder>();
		turnSequence = turnSucceeder->SetChild<Sequence>();
		isturn = turnSequence->AddChild<IsTurn>();
		playanima[0] = turnSequence->AddChild<PlayAnimaion>();
		guppyturn = turnSequence->AddChild<GuppyTurn>();

		swimSequence = _Sequence->AddChild<Sequence>();
		dropCoin = swimSequence->AddChild<DropCoin>();
		playanima[1] = swimSequence->AddChild<PlayAnimaion>();
		move = swimSequence->AddChild<Move>();

	}
	void GuppyBehaviorTree::Update()
	{
		Run();
	}
	void GuppyBehaviorTree::LateUpdate()
	{
	}
	void GuppyBehaviorTree::Render()
	{
	}
	void GuppyBehaviorTree::OnCollisionEnter(Collider2D* other)
	{
		_BlackBoard->AddData(L"otherColl", other);
		_BlackBoard->SetData(L"CollisionEnter", true);
	}
	void GuppyBehaviorTree::OnCollisionStay(Collider2D* other)
	{
		_BlackBoard->AddData(L"otherColl", other);
		_BlackBoard->SetData(L"CollisionEnter", false);
		_BlackBoard->SetData(L"CollisionStay", true);
	}
	void GuppyBehaviorTree::OnCollisionExit(Collider2D* other)
	{
		_BlackBoard->SetData(L"CollisionEnter", false);
		_BlackBoard->SetData(L"CollisionStay", false);
	}
	void GuppyBehaviorTree::Run()
	{
		_Root->Run();
	}
}
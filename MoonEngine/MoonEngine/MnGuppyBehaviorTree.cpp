#include "MnGuppyBehaviorTree.h"

#include "MnGuppyDeath.h"
#include "MnDestroyFish.h"


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
#include "MnGuppyFoodTurn.h"
#include "MnMove2Food.h"
#include "MnEatFood.h"
#include "MnAddLevel.h"

#include "MnKdTree.h"

#include "playScene.h"
#include "MnFood.h"

#include "MnConstantBuffer.h"
#include "MnRenderer.h"
#include "MnMeshRenderer.h"

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
		UINT level = 1;
		int HungryStack=0;
		UINT levelStack = 0;

		KdTree* foodtree =Mn::kdTree;

		//setData
		_BlackBoard->AddData<GameObject>(L"Owner", GetOwner());
		_BlackBoard->AddData<KdTree>(L"Food_Tree", foodtree);

		PlayAnimaion* anima = new PlayAnimaion(_BlackBoard.get());
		_BlackBoard->AddData<PlayAnimaion>(L"AnimationPlay", anima);

		_BlackBoard->MakeData<int>(L"HungryStack");
		_BlackBoard->SetData(L"HungryStack", HungryStack);
		_BlackBoard->MakeData<UINT>(L"Level");
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

		_BlackBoard->MakeData<eFishType>(L"Fish_Type");
		_BlackBoard->SetData(L"Fish_Type", eFishType::Guppy);

		_BlackBoard->MakeData<double>(L"End");
		_BlackBoard->SetData(L"End", 0.0f);

		_BlackBoard->MakeData<Vector3>(L"Food_Pos");
		_BlackBoard->SetData<Vector3>(L"Food_Pos", Vector3::Zero);


		Selector* mainSelector;


		//Death
		Sequence* deathSequence;
		GuppyDeath* isDeath;
		DestroyFish* destroyFish;

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
		GuppyFoodTurn* foodTurn;
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

		mainSelector = _Root->setChild<Selector>();
		deathSequence = mainSelector->AddChild<Sequence>();
		isDeath = deathSequence->AddChild<GuppyDeath>();
		destroyFish = deathSequence->AddChild<DestroyFish>();

		_Sequence = mainSelector->AddChild <Sequence>();
		HungrySucceder = _Sequence->AddChild<Succeeder>();
		HungrySequence = HungrySucceder->SetChild<Sequence>();
		addStack = HungrySequence->AddChild<AddHungryStack>();
		isHungry = HungrySequence->AddChild<IsHungry>();

		Hungryrepeat = HungrySequence->AddChild<RepeatUntilFail>();
		eatSequence = Hungryrepeat->SetChild<Sequence>();

		findFood = eatSequence->AddChild<FindFood>();
		eatInverter = eatSequence->AddChild<Inverter>();

		eatSequence_ = eatInverter->SetChild<Sequence>();
		
		foodTurn = eatSequence_->AddChild<GuppyFoodTurn>();
		move2food = eatSequence_->AddChild<Move2Food>();

		turnSucceeder = _Sequence->AddChild<Succeeder>();
		turnSequence = turnSucceeder->SetChild<Sequence>();
		isturn = turnSequence->AddChild<IsTurn>();
		guppyturn = turnSequence->AddChild<GuppyTurn>();

		swimSequence = _Sequence->AddChild<Sequence>();
		dropCoin = swimSequence->AddChild<DropCoin>();
		playanima[1] = swimSequence->AddChild<PlayAnimaion>();
		move = swimSequence->AddChild<Move>();


		//노드 저장
		_BlackBoard->AddData<GuppyFoodTurn>(L"FoodTurnNode", foodTurn);

	}
	void GuppyBehaviorTree::Update()
	{
		Run();
		MeshRenderer* MR = GetOwner()->GetComponent<MeshRenderer>();
		enums::eDir dir = _BlackBoard->GetDataValue<enums::eDir>(L"Dir");
		if (dir == eDir::Right)
			MR->FlipX(1);
		else
			MR->FlipX(0);
	}
	void GuppyBehaviorTree::LateUpdate()
	{
	}
	void GuppyBehaviorTree::Render()
	{

	}
	void GuppyBehaviorTree::OnCollisionEnter(Collider2D* other)
	{
		eFishState hungrystate = _BlackBoard->GetDataValue<eFishState>(L"Fish_State");
		if (hungrystate!=eFishState::Full && other->GetOwner()->GetName() == L"Food")
		{
			_BlackBoard->SetData(L"Behavior", enums::eBehavior::Eat);
			_BlackBoard->SetData(L"HungryStack", 0);
			_BlackBoard->SetData(L"Fish_State", eFishState::Full);

			UINT stack = _BlackBoard->GetDataValue<UINT>(L"Level_Stack");
			stack += 1;
			_BlackBoard->SetData(L"Level_Stack", stack);
			
			AddLevel* addlevel = new AddLevel(_BlackBoard.get());
			addlevel->Run();

			other->GetOwner()->OnClick();
		}
	}
	void GuppyBehaviorTree::OnCollisionStay(Collider2D* other)
	{

	}
	void GuppyBehaviorTree::OnCollisionExit(Collider2D* other)
	{
	}
	void GuppyBehaviorTree::Run()
	{
		_Root->Run();
	}
	UINT GuppyBehaviorTree::GetGuppyLevel()
	{
		return _BlackBoard->GetDataValue<UINT>(L"Level");
	}
	bool GuppyBehaviorTree::GetGuppyStarving()
	{
		if (_BlackBoard->GetDataValue<eFishState>(L"Fish_State") == eFishState::Starving)
			return true;
		else
			return false;
	}
}
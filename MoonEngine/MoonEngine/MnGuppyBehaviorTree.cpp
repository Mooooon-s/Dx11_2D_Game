#include "MnGuppyBehaviorTree.h"

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

#include "MnKdTree.h"

#include "playScene.h"

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
	GuppyBehaviorTree::GuppyBehaviorTree(GameObject* guppy)
		: _Guppy(guppy)
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

		KdTree* foodtree =Mn::kdTree;


		//setData
		_BlackBoard->AddData<GameObject>(L"Guppy", _Guppy);
		_BlackBoard->AddData<KdTree>(L"Food_Tree", foodtree);


		_BlackBoard->MakeData<int>(L"HungryStack");
		_BlackBoard->SetData(L"HungryStack", HungryStack);
		_BlackBoard->MakeData<float>(L"Level");
		_BlackBoard->SetData(L"Level", level);
		_BlackBoard->MakeData<float>(L"MoveSpeed");
		_BlackBoard->SetData(L"MoveSpeed", speed);
		
		_BlackBoard->MakeData<eBehavior>(L"Behavior");
		_BlackBoard->SetData(L"Behavior", behavior);
		_BlackBoard->MakeData<eFishState>(L"Fish_State");
		_BlackBoard->SetData(L"Fish_State", fishstate);
		_BlackBoard->MakeData<eDir>(L"Dir");
		_BlackBoard->SetData(L"Dir", dir);

		_BlackBoard->MakeData<double>(L"End");
		_BlackBoard->SetData(L"End", 0.0f);
		


		//Hungry
		Succeeder* HungrySucceder;
		Selector* HungrySelector;
		Sequence* HungrySequence;
		AddHungryStack* addStack;
		IsHungry* isHungry;
		RepeatUntilFail* Hungryrepeat;
		Sequence* eatSequence;
		FindFood* findFood;
		

		//turn
		Succeeder* turnSucceeder;
		Sequence* turnSequence;
		IsTurn* isturn;
		GuppyTurn* guppyturn;
		
		//swim
		Sequence* swimSequence;
		
		//condition

		//action Node
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

		turnSucceeder = _Sequence->AddChild<Succeeder>();
		turnSequence = turnSucceeder->SetChild<Sequence>();
		isturn = turnSequence->AddChild<IsTurn>();
		playanima[0] = turnSequence->AddChild<PlayAnimaion>();
		guppyturn = turnSequence->AddChild<GuppyTurn>();

		swimSequence = _Sequence->AddChild<Sequence>();
		playanima[1] = swimSequence->AddChild<PlayAnimaion>();
		move = swimSequence->AddChild<Move>();
		
		
		
		int a = 0;
	}
	void GuppyBehaviorTree::Run()
	{
		_Root->Run();
	}
}
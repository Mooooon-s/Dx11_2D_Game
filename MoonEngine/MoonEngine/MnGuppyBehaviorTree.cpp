#include "MnGuppyBehaviorTree.h"

#include "MnFindFood.h"
#include "MnMove.h"
#include "MnPlayAnimaion.h"
#include "MnIsTurn.h"
#include "MnGuppyTurn.h"

#include "MnAnimation.h"
#include "MnGameObject.h"
#include "MnRandomSelector.h"

#include "MnKdTree.h"

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
		bool IsHungry = false;
		float speed = 0.8f;
		eBehavior behavior = eBehavior::Swim;
		eFishState fishstate = eFishState::Full;
		eDir dir = eDir::Left;
		float level = 1;
		int HungryStack=0;

		KdTree* foodtree = nullptr;


		//setData
		_BlackBoard->AddData<GameObject>(L"Guppy", _Guppy);
		_BlackBoard->AddData<KdTree>(L"Food_Tree", foodtree);


		_BlackBoard->MakeData<bool>(L"Hungry");
		_BlackBoard->SetData(L"Hungry", IsHungry);
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
		


		_Root = new RootNode(_BlackBoard.get());



		_Sequence = _Root->setChild<Sequence>();
		Sequence* swimSequence;
		Sequence* turnSequence;
		Selector* turnSelector;
		Succeeder* turnSucceeder;
		IsTurn* isturn;
		GuppyTurn* guppyturn;
		//condition
		FindFood* findFood;

		//action Node
		Move* move;
		PlayAnimaion* playanima[2];
		
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
#include "MnGusBehaviorTree.h"
#include "MnFish.h"
#include "MnFood.h"

#include "..\Engine_SOURCE\MnBlackBoard.h"
#include "..\Engine_SOURCE\MnRootNode.h"
#include "..\Engine_SOURCE\MnSequence.h"
#include "..\Engine_SOURCE\MnSelector.h"
#include "..\Engine_SOURCE\MnSucceeder.h"
#include "..\Engine_SOURCE\MnInverter.h"

#include "MnGusAnimatorCntrl.h"

#include "MnMonIsDead.h"
#include "MnGetDemaged.h"
#include "MnFindFish.h"
#include "MnMove2Fish.h"
#include "MnMeshRenderer.h"
#include "MnGameObject.h"

#include "MnFindFood.h"
#include "MnMove2Target.h"
#include "MnKdTree.h"
#include "PLAYSCENE.H"
#include "MnTurn2Target.h"

namespace Mn
{
	GusBehaviorTree::GusBehaviorTree()
		: _BlackBoard(nullptr)
		, _Root(nullptr)
		, _GetDemage(nullptr)
	{
	}
	GusBehaviorTree::~GusBehaviorTree()
	{
	}
	void GusBehaviorTree::Initialize()
	{
		_BlackBoard = new BlackBoard();

		_GetDemage = new GetDemaged(_BlackBoard);
		_BlackBoard->AddData<GameObject>(L"Owner",GetOwner());

		KdTree* foodtree = Mn::kdTree;
		_BlackBoard->AddData<KdTree>(L"Food_Tree", foodtree);

		_BlackBoard->MakeData<eDir>(L"Dir");
		_BlackBoard->SetData(L"Dir", eDir::Left);
		_BlackBoard->MakeData<int>(L"Hp");
		_BlackBoard->SetData(L"Hp", 50);

		_BlackBoard->MakeData<float>(L"MoveSpeed");
		_BlackBoard->SetData(L"MoveSpeed", 0.8f);

		_BlackBoard->MakeData<eBossType>(L"BossType");
		_BlackBoard->SetData(L"BossType", eBossType::Gus);

		_BlackBoard->MakeData<Vector3>(L"Target_Pos");
		_BlackBoard->SetData(L"Target_Pos", Vector3::Zero);

		_BlackBoard->MakeData<Vector3>(L"Food_Pos");
		_BlackBoard->SetData(L"Food_Pos", Vector3::Zero);

		_BlackBoard->MakeData<float>(L"Alpha");
		_BlackBoard->SetData(L"Alpha", 1.0f);

		_BlackBoard->ResetRunningNode();

		_Root = new RootNode(_BlackBoard);
		_Root->SetTimer();
		Sequence* sequence = _Root->setChild<Sequence>();

		Inverter* inverter = sequence->AddChild<Inverter>();
		MonIsDead* isDead = inverter->SetChild<MonIsDead>();

		Selector* selector = sequence->AddChild<Selector>();

		Sequence* foodSequence = selector->AddChild<Sequence>();
		Inverter* foodInverter = foodSequence->AddChild<Inverter>();
		FindFood* findFood = foodInverter->SetChild<FindFood>();
		Inverter* fishInverter = foodSequence->AddChild<Inverter>();
		FindFish* findFish = fishInverter->SetChild<FindFish>();


		Sequence* movesequence = selector->AddChild<Sequence>();
		Turn2Target* turn2target = movesequence->AddChild<Turn2Target>();
		GusAnimatorCntrl* GAC = movesequence->AddChild<GusAnimatorCntrl>();
		Move2Target* move2target = movesequence->AddChild<Move2Target>();


		_BlackBoard->AddData<FindFood>(L"Find_Food_Node", findFood);

	}
	void GusBehaviorTree::Update()
	{
		_Root->Run();
		MeshRenderer* MR = GetOwner()->GetComponent<MeshRenderer>();
		enums::eDir dir = _BlackBoard->GetDataValue<enums::eDir>(L"Dir");
		float alpha = _BlackBoard->GetDataValue<float>(L"Alpha");
		if (dir == eDir::Right)
			MR->FlipX(1);
		else
			MR->FlipX(0);

		MR->AlphaValue(alpha);
	}
	void GusBehaviorTree::LateUpdate()
	{
	}
	void GusBehaviorTree::Render()
	{
	}
	void GusBehaviorTree::OnCollisionEnter(Collider2D* other)
	{
		if (dynamic_cast<Fish*>(other->GetOwner()))
		{
			dynamic_cast<Fish*>(other->GetOwner())->State(GameObject::eState::Dead);
		}
		else if (dynamic_cast<Food*>(other->GetOwner()))
		{
			//int hp = _BlackBoard->GetDataValue<int>(L"Hp");
			//hp -= 10;
			//_BlackBoard->SetData(L"Hp", hp);
			_GetDemage->Run();
			Resources::Find<AudioClip>(L"Eat_Food")->SoundPlay();
			dynamic_cast<Food*>(other->GetOwner())->State(GameObject::eState::Dead);
		}
	}
}
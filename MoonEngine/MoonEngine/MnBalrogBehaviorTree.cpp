#include "MnBalrogBehaviorTree.h"


#include "..\Engine_SOURCE\MnBlackBoard.h"
#include "..\Engine_SOURCE\MnRootNode.h"
#include "..\Engine_SOURCE\MnSequence.h"
#include "..\Engine_SOURCE\MnSelector.h"
#include "..\Engine_SOURCE\MnSucceeder.h"
#include "..\Engine_SOURCE\MnInverter.h"

#include "MnMonIsDead.h"
#include "MnGetDemaged.h"
#include "MnFindFish.h"
#include "MnMove2Fish.h"
#include "MnMeshRenderer.h"
#include "MnGameObject.h"

#include "MnFish.h"

namespace Mn
{
	BalrogBehaviorTree::BalrogBehaviorTree()
		: _BlackBorad(nullptr)
		, _GetDemage(nullptr)
		, _Root(nullptr)
	{
	}
	BalrogBehaviorTree::~BalrogBehaviorTree()
	{
	}
	void BalrogBehaviorTree::Initialize()
	{
		_BlackBorad  = new BlackBoard();

		_GetDemage = new GetDemaged(_BlackBorad);
		_BlackBorad->AddData<GameObject>(L"Owner", GetOwner());

		_BlackBorad->MakeData<eDir>(L"Dir");
		_BlackBorad->SetData(L"Dir", eDir::Left);
		_BlackBorad->MakeData<int>(L"Hp");
		_BlackBorad->SetData(L"Hp", 50);
		_BlackBorad->MakeData<bool>(L"GetDamege");
		_BlackBorad->SetData(L"GetDamege", false);
		_BlackBorad->MakeData<Vector3>(L"MousePos");
		_BlackBorad->SetData(L"MousePos", Vector3::Zero);

		_BlackBorad->MakeData<float>(L"StunTime");
		_BlackBorad->SetData(L"StunTime", 0.0f);

		_BlackBorad->MakeData<eBossType>(L"BossType");
		_BlackBorad->SetData(L"BossType", eBossType::Barlog);

		Vector3 targetPos = Vector3::Zero;
		_BlackBorad->MakeData<Vector3>(L"Target_Pos");
		_BlackBorad->SetData(L"Target_Pos", targetPos);

		_BlackBorad->MakeData<float>(L"Alpha");
		_BlackBorad->SetData(L"Alpha", 1.0f);

		_Root = new RootNode(_BlackBorad);
		_Root->SetTimer();
		Sequence* sequence = _Root->setChild<Sequence>();

		Inverter* inverter = sequence->AddChild<Inverter>();
		MonIsDead* isDead = inverter->SetChild<MonIsDead>();

		FindFish* findFish = sequence->AddChild<FindFish>();
		Move2Fish* move2Fish = sequence->AddChild<Move2Fish>();

		_BlackBorad->AddData<MonIsDead>(L"IsDeadNode", isDead);
	}
	void BalrogBehaviorTree::Update()
	{
		_Root->Run();
		MeshRenderer* MR = GetOwner()->GetComponent<MeshRenderer>();
		enums::eDir dir = _BlackBorad->GetDataValue<enums::eDir>(L"Dir");
		float alpha = _BlackBorad->GetDataValue<float>(L"Alpha");
		if (dir == eDir::Right)
			MR->FlipX(1);
		else
			MR->FlipX(0);

		MR->AlphaValue(alpha);
	}
	void BalrogBehaviorTree::LateUpdate()
	{
	}
	void BalrogBehaviorTree::Render()
	{
	}
	void BalrogBehaviorTree::OnCollisionEnter(Collider2D* other)
	{
		if (!_BlackBorad->GetDataValue<bool>(L"GetDamege"))
		{
			if (dynamic_cast<Fish*>(other->GetOwner()))
			{
				dynamic_cast<Fish*>(other->GetOwner())->State(GameObject::eState::Dead);
			}
		}
	}
	void BalrogBehaviorTree::OnClick(Vector3 pos)
	{
		_BlackBorad->SetData(L"GetDamege", true);
		_BlackBorad->SetData(L"StunTime", 0.0f);
		_BlackBorad->SetData(L"MousePos", pos);
		_GetDemage->Run();
	}
}
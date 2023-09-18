#include "MnBalrogBehaviorTree.h"


#include "..\Engine_SOURCE\MnBlackBoard.h"
#include "..\Engine_SOURCE\MnRootNode.h"
#include "..\Engine_SOURCE\MnSequence.h"
#include "..\Engine_SOURCE\MnSelector.h"
#include "..\Engine_SOURCE\MnSucceeder.h"
#include "..\Engine_SOURCE\MnInverter.h"

#include "MnBalIsDead.h"
#include "MnGetDemaged.h"
#include "MnFindFish.h"
#include "MnMove2Fish.h"
#include "MnMeshRenderer.h"
#include "MnGameObject.h"

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
		_BlackBorad->AddData<GameObject>(L"Balrog", GetOwner());

		_BlackBorad->MakeData<eDir>(L"Dir");
		_BlackBorad->SetData(L"Dir", eDir::Left);
		_BlackBorad->MakeData<UINT>(L"Hp");
		_BlackBorad->SetData(L"Hp", 20);
		_BlackBorad->MakeData<bool>(L"GetDamege");
		_BlackBorad->SetData(L"GetDamege", false);
		_BlackBorad->MakeData<Vector3>(L"MousePos");
		_BlackBorad->SetData(L"MousePos", Vector3::Zero);

		Vector3 targetPos = Vector3::Zero;
		_BlackBorad->MakeData<Vector3>(L"Target_Pos");
		_BlackBorad->SetData(L"Target_Pos", targetPos);

		_Root = new RootNode(_BlackBorad);
		_Root->SetTimer();
		Sequence* sequence = _Root->setChild<Sequence>();
		Inverter* inverter = sequence->AddChild<Inverter>();
		BalIsDead* isDead = inverter->SetChild<BalIsDead>();

		FindFish* findFish = sequence->AddChild<FindFish>();
		Move2Fish* move2Fish = sequence->AddChild<Move2Fish>();

		 
	}
	void BalrogBehaviorTree::Update()
	{
		_Root->Run();
		MeshRenderer* MR = GetOwner()->GetComponent<MeshRenderer>();
		enums::eDir dir = _BlackBorad->GetDataValue<enums::eDir>(L"Dir");
		if (dir == eDir::Right)
			MR->FlipX(1);
		else
			MR->FlipX(0);
	}
	void BalrogBehaviorTree::LateUpdate()
	{
	}
	void BalrogBehaviorTree::Render()
	{
	}
	void BalrogBehaviorTree::OnClick(Vector3 pos)
	{
		_BlackBorad->SetData(L"GetDamege", true);
		_BlackBorad->SetData(L"MousePos", pos);
		_GetDemage->Run();
	}
}
#include "MnBalrogBehaviorTree.h"


#include "..\Engine_SOURCE\MnBlackBoard.h"
#include "..\Engine_SOURCE\MnRootNode.h"
#include "..\Engine_SOURCE\MnSequence.h"
#include "..\Engine_SOURCE\MnSelector.h"
#include "..\Engine_SOURCE\MnSucceeder.h"
#include "..\Engine_SOURCE\MnInverter.h"

#include "MnBalIsDead.h"
#include "MnGetDemaged.h"


namespace Mn
{
	BalrogBehaviorTree::BalrogBehaviorTree()
		:_GetDemage(nullptr)
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
		_BlackBorad->MakeData<UINT>(L"Hp");
		_BlackBorad->SetData(L"Hp", 20);

		_Root = new RootNode(_BlackBorad);
		_Root->SetTimer();
		Sequence* sequence = _Root->setChild<Sequence>();
		Inverter* inverter = sequence->AddChild<Inverter>();
		BalIsDead* isDead = inverter->SetChild<BalIsDead>();

		 
	}
	void BalrogBehaviorTree::Update()
	{
		_Root->Run();
	}
	void BalrogBehaviorTree::LateUpdate()
	{
	}
	void BalrogBehaviorTree::Render()
	{
	}
	void BalrogBehaviorTree::OnClick()
	{
		_GetDemage->Run();
	}
}
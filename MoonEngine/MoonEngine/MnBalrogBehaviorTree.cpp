#include "MnBalrogBehaviorTree.h"


#include "..\Engine_SOURCE\MnBlackBoard.h"
#include "..\Engine_SOURCE\MnRootNode.h"
#include "..\Engine_SOURCE\MnSequence.h"
#include "..\Engine_SOURCE\MnSelector.h"
#include "..\Engine_SOURCE\MnSucceeder.h"
#include "..\Engine_SOURCE\MnInverter.h"

#include "MnBalIsDead.h"


namespace Mn
{
	BalrogBehaviorTree::BalrogBehaviorTree()
	{
	}
	BalrogBehaviorTree::~BalrogBehaviorTree()
	{
	}
	void BalrogBehaviorTree::Initialize()
	{
		BlackBoard* blackBorad = new BlackBoard();

		blackBorad->AddData<GameObject>(L"Balrog", GetOwner());
		blackBorad->MakeData<UINT>(L"Hp");
		blackBorad->SetData(L"Hp", 20);

		RootNode* root = new RootNode(blackBorad);
		Sequence* sequence = root->setChild<Sequence>();
		Inverter* inverter = sequence->AddChild<Inverter>();
		BalIsDead* isDead = inverter->SetChild<BalIsDead>();

		 
	}
	void BalrogBehaviorTree::Update()
	{
	}
	void BalrogBehaviorTree::LateUpdate()
	{
	}
	void BalrogBehaviorTree::Render()
	{
	}
}
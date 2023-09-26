#include "MnCaniboarBehaviorTree.h"

#include "MnSwim.h"
#include "MnRootNode.h"
#include "MnSequence.h"
#include "MnSelector.h"
#include "MnInverter.h"
#include "MnSucceeder.h"

#include "MnMeshRenderer.h"
#include "MnGameObject.h"
#include "MnCaniBoarAnimatonCntrl.h"
#include "MnIsTurn.h"

#include "MnMove.h"


namespace Mn
{
	CaniboarBehaviorTree::CaniboarBehaviorTree()
		: _BlackBoard(nullptr)
	{
	}
	CaniboarBehaviorTree::~CaniboarBehaviorTree()
	{
	}
	void CaniboarBehaviorTree::Initialize()
	{
		_BlackBoard = std::make_shared<BlackBoard>();

		CaniBoarAnimatonCntrl* CBAC = new CaniBoarAnimatonCntrl(_BlackBoard.get());
		_BlackBoard->AddData<CaniBoarAnimatonCntrl>(L"AnimaCntrl", CBAC);

		_BlackBoard->AddData<GameObject>(L"Owner", GetOwner());

		_BlackBoard->MakeData<eDir>(L"Dir");
		_BlackBoard->SetData(L"Dir", eDir::Left);

		_BlackBoard->MakeData<float>(L"MoveSpeed");
		_BlackBoard->SetData(L"MoveSpeed",0.8f);

		_BlackBoard->MakeData<eFishType>(L"Fish_Type");
		_BlackBoard->SetData(L"Fish_Type", eFishType::CaniBoar);

		_BlackBoard->MakeData<eFishState>(L"Fish_State");
		_BlackBoard->SetData(L"Fish_State", eFishState::Full);

		_BlackBoard->MakeData<eBehavior>(L"Behavior");
		_BlackBoard->SetData(L"Behavior", eBehavior::Swim);

		_Root = new RootNode(_BlackBoard.get());
		Selector* rootSelector = _Root->setChild<Selector>();
		
		
		Sequence* swimSequence = rootSelector->AddChild<Sequence>();
		Succeeder* turnSucceder = swimSequence->AddChild<Succeeder>();
		IsTurn* isturn = turnSucceder->SetChild<IsTurn>();
		Move* swim = swimSequence->AddChild<Move>();

		_Root->SetTimer();
	}
	void CaniboarBehaviorTree::Update()
	{
		_Root->Run();
		MeshRenderer* MR = GetOwner()->GetComponent<MeshRenderer>();
		enums::eDir dir = _BlackBoard->GetDataValue<enums::eDir>(L"Dir");
		if (dir == eDir::Right)
			MR->FlipX(1);
		else
			MR->FlipX(0);
	}
	void CaniboarBehaviorTree::LateUpdate()
	{
	}
	void CaniboarBehaviorTree::Render()
	{
	}
	void CaniboarBehaviorTree::OnCollisionEnter(Collider2D* other)
	{
	}
	void CaniboarBehaviorTree::OnCollisionStay(Collider2D* other)
	{
	}
	void CaniboarBehaviorTree::OnCollisionExit(Collider2D* other)
	{
	}
}
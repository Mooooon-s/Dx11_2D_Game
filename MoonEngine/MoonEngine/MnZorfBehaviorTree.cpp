#include "MnZorfBehaviorTree.h"
#include "MnMeshRenderer.h"
#include "MnGameObject.h"

#include "MnSequence.h"
#include "MnSelector.h"
#include "MnInverter.h"
#include "MnSucceeder.h"
#include "MnIsTurn.h"
#include "MnFishTurn.h"

#include "MnZorfAnimationCntrl.h"

namespace Mn
{
	ZorfBehaviorTree::ZorfBehaviorTree()
		: _BlackBoard(nullptr)
		, _Root(nullptr)
	{
	}
	ZorfBehaviorTree::~ZorfBehaviorTree()
	{
	}
	void ZorfBehaviorTree::Initialize()
	{
		_BlackBoard = std::make_shared<BlackBoard>();

		ZorfAnimationCntrl* ZAC = new ZorfAnimationCntrl(_BlackBoard.get());
		_BlackBoard->AddData<ZorfAnimationCntrl>(L"AnimaCntrl", ZAC);

		_BlackBoard->AddData<GameObject>(L"Owner", GetOwner());

		_BlackBoard->MakeData<eDir>(L"Dir");
		_BlackBoard->SetData(L"Dir", eDir::Left);

		_BlackBoard->MakeData<float>(L"MoveSpeed");
		_BlackBoard->SetData(L"MoveSpeed", 0.8f);

		_BlackBoard->MakeData<eBehavior>(L"Behavior");
		_BlackBoard->SetData(L"Behavior", eBehavior::Swim);

		_BlackBoard->MakeData<eFishType>(L"Fish_Type");
		_BlackBoard->SetData(L"Fish_Type", eFishType::Zorf);

		_BlackBoard->MakeData<eFishState>(L"Fish_State");
		_BlackBoard->SetData(L"Fish_State", eFishState::Full);

		_Root = new RootNode(_BlackBoard.get());
		_Root->SetTimer();

		Selector* selector = _Root->setChild<Selector>();


		Sequence* swimSequence = selector->AddChild<Sequence>();
		Succeeder* turnSucceder = swimSequence->AddChild<Succeeder>();
		Sequence* turnSequence = turnSucceder->SetChild<Sequence>();
		IsTurn* isturn = turnSequence->AddChild<IsTurn>();
		FishTurn* fishTurn = turnSequence->AddChild<FishTurn>();



	}
	void ZorfBehaviorTree::Update()
	{
		_Root->Run();
		MeshRenderer* MR = GetOwner()->GetComponent<MeshRenderer>();
		enums::eDir dir = _BlackBoard->GetDataValue<enums::eDir>(L"Dir");
		if (dir == eDir::Right)
			MR->FlipX(1);
		else
			MR->FlipX(0);
	}
	void ZorfBehaviorTree::LateUpdate()
	{
	}
	void ZorfBehaviorTree::Render()
	{
	}
	void ZorfBehaviorTree::OnCollisionEnter(Collider2D* other)
	{
	}
	void ZorfBehaviorTree::OnCollisionStay(Collider2D* other)
	{
	}
	void ZorfBehaviorTree::OnCollisionExit(Collider2D* other)
	{
	}
}
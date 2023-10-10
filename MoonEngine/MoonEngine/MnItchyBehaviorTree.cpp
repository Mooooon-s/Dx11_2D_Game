#include "MnItchyBehaviorTree.h"

#include "MnMeshRenderer.h"

#include "MnSelector.h"
#include "MnSequence.h"
#include "MnInverter.h"
#include "MnSucceeder.h"
#include "MnRepeatUntilFail.h"

#include "MnMove.h"
#include "MnIsTurn.h"
#include "MnFishTurn.h"
#include "MnItchyAnimationCntrl.h"
#include "MnDetectBoss.h"
#include "MnGetBossPosition.h"
#include "MnMove2Boss.h"
#include "MnRush2Boss.h"


namespace Mn
{
	ItchyBehaviorTree::ItchyBehaviorTree()
		: _BlackBoard(nullptr)
	{
	}
	ItchyBehaviorTree::~ItchyBehaviorTree()
	{
	}
	void ItchyBehaviorTree::Initialize()
	{
		_BlackBoard = std::make_shared<BlackBoard>();

		ItchyAnimationCntrl* IAC = new ItchyAnimationCntrl(_BlackBoard.get());

		_BlackBoard->AddData<GameObject>(L"Owner", GetOwner());

		_BlackBoard->MakeData<eDir>(L"Dir");
		_BlackBoard->SetData(L"Dir", eDir::Left);

		_BlackBoard->MakeData<float>(L"MoveSpeed");
		_BlackBoard->SetData(L"MoveSpeed", 0.2f);

		_BlackBoard->MakeData<eBehavior>(L"Behavior");
		_BlackBoard->SetData(L"Behavior", eBehavior::Swim);

		_BlackBoard->MakeData<eFishType>(L"Fish_Type");
		_BlackBoard->SetData(L"Fish_Type", eFishType::Itchy);

		_BlackBoard->MakeData<eFishState>(L"Fish_State");
		_BlackBoard->SetData(L"Fish_State", eFishState::Full);

		_BlackBoard->MakeData<bool>(L"AttackMode");
		_BlackBoard->SetData(L"AttackMode", false);

		_BlackBoard->MakeData<Vector3>(L"BossPos");
		_BlackBoard->SetData(L"BossPos", Vector3::Zero);

		_Root = new RootNode(_BlackBoard.get());
		_Root->SetTimer();

		Selector* rootSelector = _Root->setChild<Selector>();

		Sequence* attackSequence = rootSelector->AddChild<Sequence>();
		DetectBoss* detectBoss = attackSequence->AddChild<DetectBoss>();
		RepeatUntilFail* attckRepeatUntilFail = attackSequence->AddChild<RepeatUntilFail>();
		Sequence* repeatSequence = attckRepeatUntilFail->SetChild<Sequence>();
		GetBossPosition* getBossPos = repeatSequence->AddChild<GetBossPosition>();
		Move2Boss* move2boss = repeatSequence->AddChild<Move2Boss>();
		Rush2Boss* rush2Boss = repeatSequence->AddChild<Rush2Boss>();


		Sequence* swimSequence = rootSelector->AddChild<Sequence>();
		Succeeder* turnSucceder = swimSequence->AddChild<Succeeder>();
		Sequence* turnSequence = turnSucceder->SetChild<Sequence>();
		IsTurn* isturn = turnSequence->AddChild<IsTurn>();
		FishTurn* fishTurn = turnSequence->AddChild<FishTurn>();

		ItchyAnimationCntrl* animaCntrl = swimSequence->AddChild<ItchyAnimationCntrl>();
		Move* swim = swimSequence->AddChild<Move>();

		_BlackBoard->AddData<ItchyAnimationCntrl>(L"AnimaCntrl", animaCntrl);
		_BlackBoard->AddData<GetBossPosition>(L"GetBossPosNode", getBossPos);

	}
	void ItchyBehaviorTree::Update()
	{
		_Root->Run();
		MeshRenderer* MR = GetOwner()->GetComponent<MeshRenderer>();
		enums::eDir dir = _BlackBoard->GetDataValue<enums::eDir>(L"Dir");
		if (dir == eDir::Right)
			MR->FlipX(1);
		else
			MR->FlipX(0);
	}
	void ItchyBehaviorTree::LateUpdate()
	{
	}
	void ItchyBehaviorTree::Render()
	{
	}
	void ItchyBehaviorTree::OnCollisionEnter(Collider2D* other)
	{
	}
	void ItchyBehaviorTree::OnCollisionStay(Collider2D* other)
	{
	}
	void ItchyBehaviorTree::OnCollisionExit(Collider2D* other)
	{
	}
}
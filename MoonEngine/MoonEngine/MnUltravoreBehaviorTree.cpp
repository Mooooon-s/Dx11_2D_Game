#include "MnUltravoreBehaviorTree.h"

#include "MnSequence.h"
#include "MnSelector.h"
#include "MnSucceeder.h"
#include "MnRepeatUntilFail.h"
#include "MnInverter.h"

#include "MnIsDeath.h"
#include "MnHungryStack.h"
#include "MnHungryCheck.h"
#include "MnFindCaniboar.h"
#include "MnTurn2Food.h"
#include "MnMove2Caniboar.h"

#include "MnIsTurn.h"
#include "MnFishTurn.h"

#include "MnMove.h"
#include "MnUltravoreAnimationCntrl.h"

#include "MnGameObject.h"
#include "MnMeshRenderer.h"

#include "MnDropTresure.h"

namespace Mn
{
	UltravoreBehaviorTree::UltravoreBehaviorTree()
		: _BlackBoard(nullptr)
		, _Root(nullptr)
	{
	}
	UltravoreBehaviorTree::~UltravoreBehaviorTree()
	{
	}
	void UltravoreBehaviorTree::Initialize()
	{
		_BlackBoard = std::make_shared<BlackBoard>();

		UltravoreAnimationCntrl* UAC = new UltravoreAnimationCntrl(_BlackBoard.get());
		_BlackBoard->AddData<UltravoreAnimationCntrl>(L"AnimaCntrl", UAC);

		_BlackBoard->AddData<GameObject>(L"Owner", GetOwner());

		_BlackBoard->MakeData<eDir>(L"Dir");
		_BlackBoard->SetData(L"Dir", eDir::Left);

		_BlackBoard->MakeData<float>(L"MoveSpeed");
		_BlackBoard->SetData(L"MoveSpeed", 0.8f);

		_BlackBoard->MakeData<eFishType>(L"Fish_Type");
		_BlackBoard->SetData(L"Fish_Type", eFishType::Ultravore);

		_BlackBoard->MakeData<eFishState>(L"Fish_State");
		_BlackBoard->SetData(L"Fish_State", eFishState::Full);

		_BlackBoard->MakeData<eBehavior>(L"Behavior");
		_BlackBoard->SetData(L"Behavior", eBehavior::Swim);

		_BlackBoard->MakeData<int>(L"HungryStack");
		_BlackBoard->SetData(L"HungryStack", 5);

		_BlackBoard->MakeData<Vector3>(L"MoveVector");
		_BlackBoard->SetData(L"MoveVector", Vector3::Zero);

		_BlackBoard->MakeData<UINT>(L"StackFlag");
		_BlackBoard->SetData(L"StackFlag", 0);

		_Root = new RootNode(_BlackBoard.get());
		_Root->SetTimer();
		Selector* rootSelector = _Root->setChild<Selector>();

		//IsDead
		IsDeath* isDeath = rootSelector->AddChild<IsDeath>();

		Sequence* sequence = rootSelector->AddChild<Sequence>();

		//Hungry
		Succeeder* hungrySucceder = sequence->AddChild<Succeeder>();
		Sequence* HungrySequence = hungrySucceder->SetChild<Sequence>();

		HungryStack* hungryStack = HungrySequence->AddChild<HungryStack>();
		HungryCheck* hungryCheck = HungrySequence->AddChild<HungryCheck>();

		RepeatUntilFail* findReapeatUntilFail = HungrySequence->AddChild<RepeatUntilFail>();
		Sequence* foodsequence = findReapeatUntilFail->SetChild<Sequence>();
		FindCaniboar* findcaniboar = foodsequence->AddChild<FindCaniboar>();
		Turn2Food* T2F = foodsequence->AddChild<Turn2Food>();
		Move2Caniboar* M2C = foodsequence->AddChild<Move2Caniboar>();

		DropTresure* DT = sequence->AddChild<DropTresure>();

		//Find Caniboare
		Sequence* swimSequence = sequence->AddChild<Sequence>();

		Succeeder* turnSucceder = swimSequence->AddChild<Succeeder>();
		Sequence* turnSequence = turnSucceder->SetChild<Sequence>();
		IsTurn* isturn = turnSequence->AddChild<IsTurn>();
		FishTurn* fishTurn = turnSequence->AddChild<FishTurn>();

		UltravoreAnimationCntrl* animaCntrl = swimSequence->AddChild<UltravoreAnimationCntrl>();
		Move* swim = swimSequence->AddChild<Move>();

		_BlackBoard->AddData<FindCaniboar>(L"FindCaniboarNode", findcaniboar);
	}
	void UltravoreBehaviorTree::Update()
	{
		_Root->Run();
		MeshRenderer* MR = GetOwner()->GetComponent<MeshRenderer>();
		enums::eDir dir = _BlackBoard->GetDataValue<enums::eDir>(L"Dir");
		if (dir == eDir::Right)
			MR->FlipX(1);
		else
			MR->FlipX(0);
	}
	void UltravoreBehaviorTree::LateUpdate()
	{
	}
	void UltravoreBehaviorTree::Render()
	{
	}
	void UltravoreBehaviorTree::OnCollisionEnter(Collider2D* other)
	{
		eFishState hungrystate = _BlackBoard->GetDataValue<eFishState>(L"Fish_State");
		if (hungrystate != eFishState::Full && other->GetOwner()->GetName() == L"CaniBoar")
		{
			_BlackBoard->SetData(L"Behavior", enums::eBehavior::Eat);
			_BlackBoard->SetData(L"HungryStack", 5);
			_BlackBoard->SetData(L"Fish_State", eFishState::Full);
			_BlackBoard->SetData(L"StackFlag", 1);
			_BlackBoard->ResetRunningNode();
			other->GetOwner()->OnClick();
		}
	}
}
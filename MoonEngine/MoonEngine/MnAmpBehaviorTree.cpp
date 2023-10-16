#include "MnAmpBehaviorTree.h"

#include "MnMeshRenderer.h"
#include "MnGameObject.h"

#include "MnAmpAnimationCntrl.h"

#include "MnSequence.h"
#include "MnSelector.h"
#include "MnInverter.h"
#include "MnSucceeder.h"

#include "MnIsCharged.h"
#include "MnGetCharge.h"

#include "MnIsTurn.h"
#include "MnFishTurn.h"
#include "MnMove.h"
#include "MnShockWave.h"

namespace Mn
{
	AmpBehaviorTree::AmpBehaviorTree()
		: _BlackBoard(nullptr)
		, _Root(nullptr)
		, _Stack(1)
	{
	}
	AmpBehaviorTree::~AmpBehaviorTree()
	{
	}
	void AmpBehaviorTree::Initialize()
	{
		_BlackBoard = std::make_shared<BlackBoard>();

		_BlackBoard->AddData<GameObject>(L"Owner", GetOwner());

		AmpAnimationCntrl* AAC = new AmpAnimationCntrl(_BlackBoard.get());
		_BlackBoard->AddData(L"AnimaCntrl", AAC);

		_BlackBoard->MakeData<eDir>(L"Dir");
		_BlackBoard->SetData(L"Dir", eDir::Left);

		_BlackBoard->MakeData<float>(L"MoveSpeed");
		_BlackBoard->SetData(L"MoveSpeed", 0.2f);

		_BlackBoard->MakeData<eBehavior>(L"Behavior");
		_BlackBoard->SetData(L"Behavior", eBehavior::Swim);

		_BlackBoard->MakeData<eFishType>(L"Fish_Type");
		_BlackBoard->SetData(L"Fish_Type", eFishType::Amp);

		_BlackBoard->MakeData<eFishState>(L"Fish_State");
		_BlackBoard->SetData(L"Fish_State", eFishState::Full);

		_BlackBoard->MakeData<bool>(L"Charged");
		_BlackBoard->SetData(L"Charged", false);

		_BlackBoard->MakeData<float>(L"UnChargedTime");
		_BlackBoard->SetData(L"UnChargedTime", 0.0f);

		_Root = new RootNode(_BlackBoard.get());
		_Root->SetTimer();

		Selector* selector = _Root->setChild<Selector>();

		Sequence* chargedSequence = selector->AddChild<Sequence>();
		Inverter* inverter = chargedSequence->AddChild<Inverter>();
		IsCharged* ischarged = inverter->SetChild<IsCharged>();
		GetCharge* getcharge = chargedSequence->AddChild<GetCharge>();

		Sequence* swimSequence = selector->AddChild<Sequence>();
		Succeeder* turnSucceder = swimSequence->AddChild<Succeeder>();
		Sequence* turnSequence = turnSucceder->SetChild<Sequence>();
		IsTurn* isturn = turnSequence->AddChild<IsTurn>();
		FishTurn* fishTurn = turnSequence->AddChild<FishTurn>();

		AmpAnimationCntrl* AACntrl = swimSequence->AddChild<AmpAnimationCntrl>();
		Move* swim = swimSequence->AddChild<Move>();


	}
	void AmpBehaviorTree::Update()
	{
		_Root->Run();
		MeshRenderer* MR = GetOwner()->GetComponent<MeshRenderer>();
		enums::eDir dir = _BlackBoard->GetDataValue<enums::eDir>(L"Dir");
		if (dir == eDir::Right)
			MR->FlipX(1);
		else
			MR->FlipX(0);
	}
	void AmpBehaviorTree::LateUpdate()
	{
	}
	void AmpBehaviorTree::Render()
	{
	}
	void AmpBehaviorTree::OnClick()
	{
		if (_BlackBoard->GetDataValue<bool>(L"Charged"))
		{
			if (_Stack < 3)
				_Stack++;
			else
			{
				_Stack = 1;
				ShockWave* SW = new ShockWave(_BlackBoard.get());
				SW->Run();
				_BlackBoard->GetData<AmpAnimationCntrl>(L"AnimaCntrl")->Run();
			}
		}
	}
}
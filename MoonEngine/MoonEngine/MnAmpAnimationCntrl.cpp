#include "MnAmpAnimationCntrl.h"

#include "MnGameObject.h"
#include "MnAnimator.h"

namespace Mn
{
	AmpAnimationCntrl::AmpAnimationCntrl()
		:_BlackBoard(nullptr)
		, _Charged(false)
	{
	}
	AmpAnimationCntrl::AmpAnimationCntrl(BlackBoard* board)
		: _BlackBoard(board)
		, _Charged(false)
	{
	}
	AmpAnimationCntrl::~AmpAnimationCntrl()
	{
	}
	enums::eBTState AmpAnimationCntrl::Run()
	{
		GameObject* owner = _BlackBoard->GetData<GameObject>(L"Owner");
		Animator* at = owner->GetComponent<Animator>();
		enums::eBehavior behavior = _BlackBoard->GetDataValue<eBehavior>(L"Behavior");
		enums::eFishState state = _BlackBoard->GetDataValue<eFishState>(L"Fish_State");
		bool charged = _BlackBoard->GetDataValue<bool>(L"Charged");

		if (charged != _Charged)
			PlayAnimation(behavior);
		_Charged = charged;

		if (!at->AnimationComplete() && _Behavior == behavior && _State != state)
			PlayAnimation(behavior);
		else if (!at->AnimationComplete() && _Behavior == behavior && _State == state)
			return enums::eBTState::SUCCESS;

		PlayAnimation(behavior);

		_State = state;
		_Behavior = behavior;

		return enums::eBTState::SUCCESS;

	}
	void AmpAnimationCntrl::PlayAnimation(enums::eBehavior behavior)
	{
		if (_BlackBoard->GetDataValue<bool>(L"Charged"))
			ChargedAnimation(behavior);
		else
			IdleAnimation(behavior);
	}
	void AmpAnimationCntrl::ChargedAnimation(enums::eBehavior behavior)
	{
		GameObject* gameObj = _BlackBoard->GetData<GameObject>(L"Owner");
		Animator* at = gameObj->GetComponent<Animator>();
		eDir dir = _BlackBoard->GetDataValue<eDir>(L"Dir");

		switch (behavior)
		{
		case Mn::enums::eBehavior::Swim:
			at->PlayAnimation(L"Amp_Charged_Swim", true);
			break;
		case Mn::enums::eBehavior::Turn:
			if (dir == eDir::Left)
				at->PlayAnimation(L"Amp_Charged_Turn", true);
			else
				at->PlayAnimation(L"Amp_Charged_Turn_Reverse", true);
			break;
		}
	}
	void AmpAnimationCntrl::IdleAnimation(enums::eBehavior behavior)
	{
		GameObject* gameObj = _BlackBoard->GetData<GameObject>(L"Owner");
		Animator* at = gameObj->GetComponent<Animator>();
		eDir dir = _BlackBoard->GetDataValue<eDir>(L"Dir");

		switch (behavior)
		{
		case Mn::enums::eBehavior::Swim:
			at->PlayAnimation(L"Amp_Swim", true);
			break;
		case Mn::enums::eBehavior::Turn:
			if (dir == eDir::Left)
				at->PlayAnimation(L"Amp_Turn", true);
			else
				at->PlayAnimation(L"Amp_Turn_Reverse", true);
			break;
		}
	}
}
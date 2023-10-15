#include "MnPregoAnimationCntrl.h"
#include "MnGameObject.h"
#include "MnAnimator.h"

namespace Mn
{
	PregoAnimationCntrl::PregoAnimationCntrl()
		: _BlackBoard(nullptr)
	{
	}
	PregoAnimationCntrl::PregoAnimationCntrl(BlackBoard* board)
		: _BlackBoard(board)
	{
	}
	PregoAnimationCntrl::~PregoAnimationCntrl()
	{
	}
	enums::eBTState PregoAnimationCntrl::Run()
	{
		GameObject* owner = _BlackBoard->GetData<GameObject>(L"Owner");
		Animator* at = owner->GetComponent<Animator>();
		enums::eBehavior behavior = _BlackBoard->GetDataValue<eBehavior>(L"Behavior");
		enums::eFishState state = _BlackBoard->GetDataValue<eFishState>(L"Fish_State");

		if (!at->AnimationComplete() && _Behavior == behavior && _State != state)
			PlayAnimation(behavior);
		else if (!at->AnimationComplete() && _Behavior == behavior && _State == state)
			return enums::eBTState::SUCCESS;

		PlayAnimation(behavior);

		_State = state;
		_Behavior = behavior;

		return enums::eBTState::SUCCESS;
	}
	void PregoAnimationCntrl::PlayAnimation(enums::eBehavior behavior)
	{
		GameObject* gameObj = _BlackBoard->GetData<GameObject>(L"Owner");
		Animator* at = gameObj->GetComponent<Animator>();
		
	
		if (_BlackBoard->GetDataValue<bool>(L"PregMent"))
			PregMentAnimation(behavior);
		else
			IdleAnimation(behavior);

	}
	void PregoAnimationCntrl::PregMentAnimation(enums::eBehavior behavior)
	{
		GameObject* gameObj = _BlackBoard->GetData<GameObject>(L"Owner");
		Animator* at = gameObj->GetComponent<Animator>();
		eDir dir = _BlackBoard->GetDataValue<eDir>(L"Dir");
	
		switch (behavior)
		{
		case Mn::enums::eBehavior::Swim:
			at->PlayAnimation(L"Prego_Preg_Swim", true);
			break;
		case Mn::enums::eBehavior::Turn:
			if (dir == eDir::Left)
				at->PlayAnimation(L"Prego_preg_Turn", true);
			else
				at->PlayAnimation(L"Prego_preg_Turn_Reverse", true);
			break;
		}

	}
	void PregoAnimationCntrl::IdleAnimation(enums::eBehavior behavior)
	{
		GameObject* gameObj = _BlackBoard->GetData<GameObject>(L"Owner");
		Animator* at = gameObj->GetComponent<Animator>();
		eDir dir = _BlackBoard->GetDataValue<eDir>(L"Dir");

		switch (behavior)
		{
		case Mn::enums::eBehavior::Swim:
			at->PlayAnimation(L"Prego_Swim", true);
			break;
		case Mn::enums::eBehavior::Turn:
			if (dir == eDir::Left)
				at->PlayAnimation(L"Prego_Turn", true);
			else
				at->PlayAnimation(L"Prego_Turn_Reverse", true);
			break;
		}
	}
	void PregoAnimationCntrl::GetPregMent()
	{
		GameObject* gameObj = _BlackBoard->GetData<GameObject>(L"Owner");
		Animator* at = gameObj->GetComponent<Animator>();

		at->PlayAnimation(L"Prego_preg_Guppy", true);
	}
	void PregoAnimationCntrl::EndPregMent()
	{
		GameObject* gameObj = _BlackBoard->GetData<GameObject>(L"Owner");
		Animator* at = gameObj->GetComponent<Animator>();

		at->PlayAnimation(L"Prego_Out_Guppy", true);
	}
}
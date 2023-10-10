#include "MnItchyAnimationCntrl.h"
#include "MnGameObject.h"
#include "MnAnimator.h"

namespace Mn
{
	ItchyAnimationCntrl::ItchyAnimationCntrl()
		: _BlackBoard(nullptr)
	{
	}
	ItchyAnimationCntrl::ItchyAnimationCntrl(BlackBoard* board)
		: _BlackBoard(board)
	{
	}
	ItchyAnimationCntrl::~ItchyAnimationCntrl()
	{
	}
	enums::eBTState ItchyAnimationCntrl::Run()
	{

		GameObject* gameObj = _BlackBoard->GetData<GameObject>(L"Owner");
		Animator* at = gameObj->GetComponent<Animator>();
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
	void ItchyAnimationCntrl::PlayAnimation(enums::eBehavior behavior)
	{
		bool attackMode = _BlackBoard->GetDataValue<bool>(L"AttackMode");
		if (attackMode)
			AttackAnimation(behavior);
		else
			IdleAnimation(behavior);
	}
	void ItchyAnimationCntrl::AttackAnimation(enums::eBehavior behavior)
	{
		GameObject* owner = _BlackBoard->GetData<GameObject>(L"Owner");
		Animator* at = owner->GetComponent<Animator>();
		eDir dir = _BlackBoard->GetDataValue<eDir>(L"Dir");
		switch (behavior)
		{
		case Mn::enums::eBehavior::Swim:
			at->PlayAnimation(L"Itchy_Attack_Swim", true);
			break;
		case Mn::enums::eBehavior::Turn:
			if (dir == eDir::Left)
				at->PlayAnimation(L"Itchy_Attack_Turn_Right", true);
			else
				at->PlayAnimation(L"Itchy_Attack_Turn_Left", true);
			break;
		default:
			break;
		}
	}
	void ItchyAnimationCntrl::IdleAnimation(enums::eBehavior behavior)
	{
		GameObject* owner = _BlackBoard->GetData<GameObject>(L"Owner");
		Animator* at = owner->GetComponent<Animator>();
		eDir dir = _BlackBoard->GetDataValue<eDir>(L"Dir"); 
		switch (behavior)
		{
		case Mn::enums::eBehavior::Swim:
			at->PlayAnimation(L"Itchy_Idle_Swim", true);
			break;
		case Mn::enums::eBehavior::Turn:
			if (dir == eDir::Left)
				at->PlayAnimation(L"Itchy_Idle_Turn_Right", true);
			else
				at->PlayAnimation(L"Itchy_Idle_Turn_Left", true);
			break;
		default:
			break;
		}
	}
}
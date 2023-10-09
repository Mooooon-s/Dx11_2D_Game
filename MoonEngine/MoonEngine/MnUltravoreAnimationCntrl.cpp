#include "MnUltravoreAnimationCntrl.h"

#include "MnGameObject.h"
#include "MnAnimator.h"

namespace Mn
{
	UltravoreAnimationCntrl::UltravoreAnimationCntrl()
		: _BlackBoard(nullptr)
	{
	}
	UltravoreAnimationCntrl::UltravoreAnimationCntrl(BlackBoard* board)
		: _BlackBoard(board)
	{
	}
	UltravoreAnimationCntrl::~UltravoreAnimationCntrl()
	{
	}
	enums::eBTState UltravoreAnimationCntrl::Run()
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
	void UltravoreAnimationCntrl::PlayAnimation(enums::eBehavior behavior)
	{
		enums::eFishState state = _BlackBoard->GetDataValue<eFishState>(L"Fish_State");

		switch (state)
		{
		case eFishState::Full:
		case eFishState::Hungry:
		case eFishState::Starving:
			FullAnimation(behavior);
			break;
		case eFishState::Death:
			DeathAnimation();
			break;
		default:
			break;
		}
	}
	void UltravoreAnimationCntrl::FullAnimation(enums::eBehavior behavior)
	{
		GameObject* gameObj = _BlackBoard->GetData<GameObject>(L"Owner");
		Animator* at = gameObj->GetComponent<Animator>();
		eDir dir = _BlackBoard->GetDataValue<eDir>(L"Dir");

		switch (behavior)
		{
		case Mn::enums::eBehavior::Swim:
			at->PlayAnimation(L"Ultravore_Swim", true);
			break;
		case Mn::enums::eBehavior::Turn:
			if (dir == eDir::Left)
			{
				at->PlayAnimation(L"Ultravore_Turn_Right", true);
			}
			else
			{
				at->PlayAnimation(L"Ultravore_Turn_Left", true);
			}
			break;
		case Mn::enums::eBehavior::Eat:
			at->PlayAnimation(L"Ultravore_Eat", true);
			break;
		}
	}
	void UltravoreAnimationCntrl::DeathAnimation()
	{
		GameObject* gameObj = _BlackBoard->GetData<GameObject>(L"Owner");
		Animator* at = gameObj->GetComponent<Animator>();
		eDir dir = _BlackBoard->GetDataValue<eDir>(L"Dir");
		if (dir == eDir::Left)
			at->PlayAnimation(L"Ultravore_Death", true);
		else
			at->PlayAnimation(L"Ultravore_Death_Reverse", true);
	}
	void UltravoreAnimationCntrl::afterAction()
	{
		GameObject* gameObj = _BlackBoard->GetData<GameObject>(L"Owner");
		Animator* at = gameObj->GetComponent<Animator>();
		if (at->AnimationComplete())
		{
			enums::eFishState state = _BlackBoard->GetDataValue<eFishState>(L"Fish_State");
			switch (state)
			{
			case eFishState::Full:
			case eFishState::Hungry:
			case eFishState::Starving:
				FullAnimation(eBehavior::Swim);
				break;
			case eFishState::Death:
				DeathAnimation();
				break;
			default:
				break;
			}
		}

		_BlackBoard->SetData(L"Behavior", eBehavior::Swim);
		_Behavior = eBehavior::Swim;
	}
}
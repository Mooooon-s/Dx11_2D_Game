#include "MnCaniBoarAnimatonCntrl.h"

#include "MnGameObject.h"
#include "MnAnimator.h"

namespace Mn
{
	CaniBoarAnimatonCntrl::CaniBoarAnimatonCntrl()
		: _BlackBoard(nullptr)
	{
	}
	CaniBoarAnimatonCntrl::CaniBoarAnimatonCntrl(BlackBoard* board)
		: _BlackBoard(board)
	{
	}
	CaniBoarAnimatonCntrl::~CaniBoarAnimatonCntrl()
	{
	}
	enums::eBTState CaniBoarAnimatonCntrl::Run()
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
	void CaniBoarAnimatonCntrl::PlayAnimation(enums::eBehavior behavior)
	{
		enums::eFishState state = _BlackBoard->GetDataValue<eFishState>(L"Fish_State");

		switch (state)
		{
		case eFishState::Full:
		case eFishState::Hungry:
			FullAnimation(behavior);
			break;
		case eFishState::Starving:
			StarvingAnimation(behavior);
			break;
		case eFishState::Death:
			DeathAnimation();
			break;
		default:
			break;
		}
	}
	void CaniBoarAnimatonCntrl::FullAnimation(enums::eBehavior behavior)
	{
		GameObject* gameObj = _BlackBoard->GetData<GameObject>(L"Owner");
		Animator* at = gameObj->GetComponent<Animator>();
		eDir dir = _BlackBoard->GetDataValue<eDir>(L"Dir");

		switch (behavior)
		{
		case Mn::enums::eBehavior::Swim:
				at->PlayAnimation(L"Caniboar_Swim", true);
			break;
		case Mn::enums::eBehavior::Turn:
			if (dir == eDir::Left)
			{
				at->PlayAnimation(L"Caniboar_Turn", true);
			}
			else
			{
				at->PlayAnimation(L"Caniboar_Turn_Reverse", true);
			}
			break;
		case Mn::enums::eBehavior::Eat:
			if (dir == eDir::Left)
				at->PlayAnimation(L"Caniboar_Eat", true);
			break;
		}
	}
	void CaniBoarAnimatonCntrl::StarvingAnimation(enums::eBehavior behavior)
	{
		GameObject* gameObj = _BlackBoard->GetData<GameObject>(L"Owner");
		Animator* at = gameObj->GetComponent<Animator>();
		eDir dir = _BlackBoard->GetDataValue<eDir>(L"Dir");

		switch (behavior)
		{
		case Mn::enums::eBehavior::Swim:
				at->PlayAnimation(L"Caniboar_Hungry_Swim", true);
			break;
		case Mn::enums::eBehavior::Turn:
			if (dir == eDir::Left)
			{
				at->PlayAnimation(L"Caniboar_Hungry_Turn", true);
			}
			else
			{
				at->PlayAnimation(L"Caniboar_Hungry_Turn_Reverse", true);
			}
			break;
		case Mn::enums::eBehavior::Eat:
			if (dir == eDir::Left)
				at->PlayAnimation(L"Caniboar_Hungry_Eat", true);
			break;
		}
	}
	void CaniBoarAnimatonCntrl::DeathAnimation()
	{
		GameObject* gameObj = _BlackBoard->GetData<GameObject>(L"Owner");
		Animator* at = gameObj->GetComponent<Animator>();
		eDir dir = _BlackBoard->GetDataValue<eDir>(L"Dir");
		if (dir == eDir::Left)
			at->PlayAnimation(L"Caniboar_Death", true);
		else
			at->PlayAnimation(L"Caniboar_Death_Reverse", true);
	}

	void CaniBoarAnimatonCntrl::afterAction()
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
				FullAnimation(eBehavior::Swim);
				break;
			case eFishState::Starving:
				StarvingAnimation(eBehavior::Swim);
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
#include "MnPlayAnimaion.h"
#include "MnPlayAnimaion.h"
#include "MnGameObject.h"
#include "MnAnimator.h"

#include "MnConstantBuffer.h"
#include "MnRenderer.h"

namespace Mn
{
	PlayAnimaion::PlayAnimaion()
		:_BlackBoard(nullptr)
	{
	}
	PlayAnimaion::PlayAnimaion(BlackBoard* blackboard)
		:_BlackBoard(blackboard)
		, _Behavior(eBehavior::Swim)
	{
		GameObject* gameObj = _BlackBoard->GetData<GameObject>(L"Owner");
		Animator* at = gameObj->GetComponent<Animator>();
		at->CompleteEvent(L"Eat_Small") = std::bind(&PlayAnimaion::afterAction,this);
		at->CompleteEvent(L"Eat_Middle") = std::bind(&PlayAnimaion::afterAction,this);
		at->CompleteEvent(L"Eat_Large") = std::bind(&PlayAnimaion::afterAction,this);
	}
	enums::eBTState PlayAnimaion::Run()
	{
		GameObject* gameObj = _BlackBoard->GetData<GameObject>(L"Owner");
		Animator* at = gameObj->GetComponent<Animator>();
		enums::eBehavior behavior =_BlackBoard->GetDataValue<eBehavior>(L"Behavior");
		enums::eFishState state = _BlackBoard->GetDataValue<eFishState>(L"Fish_State");
		if (!at->AnimationComplete() && _Behavior == behavior && _State== state)
			return enums::eBTState::SUCCESS;

		PlayAnimation(behavior);
		Bind();

		_State = state;
		_Behavior = behavior;
		return enums::eBTState::SUCCESS;
	}
	void PlayAnimaion::PlayAnimation(enums::eBehavior behavior)
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
	void PlayAnimaion::FullAnimation(enums::eBehavior behavior)
	{
		GameObject* gameObj = _BlackBoard->GetData<GameObject>(L"Owner");
		Animator* at = gameObj->GetComponent<Animator>();

		UINT level = _BlackBoard->GetDataValue<UINT>(L"Level");

		switch (behavior)
		{
		case eBehavior::Swim:
			switch (level)
			{
			case 1:
				at->PlayAnimation(L"Swim_Small", true);
				break;
			case 2:
				at->PlayAnimation(L"Swim_Middle", true);
				break;
			case 3:
				at->PlayAnimation(L"Swim_Large", true);
				break;
			default:
				break;
			}
			break;
		case eBehavior::Turn:
			switch (level)
			{
			case 1:
				if (_BlackBoard->GetDataValue<eDir>(L"Dir") == eDir::Right)
				{
					at->PlayAnimation(L"Turn_Small_Revers", true);
				}
				else
					at->PlayAnimation(L"Turn_Small", true);
				break;
			case 2:
				if (_BlackBoard->GetDataValue<eDir>(L"Dir") == eDir::Right)
					at->PlayAnimation(L"Turn_Middle_Revers", true);
				else
					at->PlayAnimation(L"Turn_Middle", true);
				break;
			case 3:
				if (_BlackBoard->GetDataValue<eDir>(L"Dir") == eDir::Right)
					at->PlayAnimation(L"Turn_Large_Revers", true);
				else
					at->PlayAnimation(L"Turn_Large", true);
				break;
			default:
				break;
			}
			break;
		case eBehavior::Eat:
			switch (level)
			{
			case 1:
				at->PlayAnimation(L"Eat_Small", true);
				break;
			case 2:
				at->PlayAnimation(L"Eat_Middle", true);
				break;
			case 3:
				at->PlayAnimation(L"Eat_Large", true);
				break;
			default:
				break;
			}
			break;
		case eBehavior::End:
			break;
		default:
			break;
		}
	}
	void PlayAnimaion::DeathAnimation()
	{
		GameObject* gameObj = _BlackBoard->GetData<GameObject>(L"Owner");
		Animator* at = gameObj->GetComponent<Animator>();

		int level = _BlackBoard->GetDataValue<float>(L"Level");

		switch (level)
		{
		case 1:
			if (_BlackBoard->GetDataValue<eDir>(L"Dir") == eDir::Right)
				at->PlayAnimation(L"Hungry_Death_Small_Reverse", false);
			else
				at->PlayAnimation(L"Hungry_Death_Small",false);
			break;
		case 2:
			if (_BlackBoard->GetDataValue<eDir>(L"Dir") == eDir::Right)
				at->PlayAnimation(L"Hungry_Death_Middle_Reverse", false);
			else
				at->PlayAnimation(L"Hungry_Death_Middle",false);
			break;
		case 3:
			if (_BlackBoard->GetDataValue<eDir>(L"Dir") == eDir::Right)
				at->PlayAnimation(L"Hungry_Death_Large_Reverse", false);
			else
				at->PlayAnimation(L"Hungry_Death_Large",false);
			break;
		default:
			break;
		}
	}
	void PlayAnimaion::StarvingAnimation(enums::eBehavior behavior)
	{
		GameObject* gameObj = _BlackBoard->GetData<GameObject>(L"Owner");
		Animator* at = gameObj->GetComponent<Animator>();

		int level = _BlackBoard->GetDataValue<float>(L"Level");

		switch (behavior)
		{
		case eBehavior::Swim:
			switch (level)
			{
			case 1:
				at->PlayAnimation(L"Hungry_Swim_Small", true);
				break;
			case 2:
				at->PlayAnimation(L"Hungry_Swim_Middle", true);
				break;
			case 3:
				at->PlayAnimation(L"Hungry_Swim_Large", true);
				break;
			default:
				break;
			}
			break;
		case eBehavior::Turn:
			switch (level)
			{
			case 1:
				if (_BlackBoard->GetDataValue<eDir>(L"Dir") == eDir::Right)
				{
					at->PlayAnimation(L"Hungry_Turn_Small_Revers", false);
				}
				else
					at->PlayAnimation(L"Hungry_Turn_Small", false);
				break;
			case 2:
				if (_BlackBoard->GetDataValue<eDir>(L"Dir") == eDir::Right)
					at->PlayAnimation(L"Hungry_Turn_Middle_Revers", false);
				else
					at->PlayAnimation(L"Hungry_Turn_Middle", false);
				break;
			case 3:
				if (_BlackBoard->GetDataValue<eDir>(L"Dir") == eDir::Right)
					at->PlayAnimation(L"Hungry_Turn_Large_Revers", false);
				else
					at->PlayAnimation(L"Hungry_Turn_Large", false);
				break;
			default:
				break;
			}
			break;
		case eBehavior::Eat:
			switch (level)
			{
			case 1:
				at->PlayAnimation(L"Hungry_Eat_Small", false);
				break;
			case 2:
				at->PlayAnimation(L"Hungry_Eat_Middle", false);
				break;
			case 3:
				at->PlayAnimation(L"Hungry_Eat_Large", false);
				break;
			default:
				break;
			}
			break;
		case eBehavior::End:
			break;
		default:
			break;
		}
	}
	void PlayAnimaion::Bind()
	{
	}
	void PlayAnimaion::afterAction()
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
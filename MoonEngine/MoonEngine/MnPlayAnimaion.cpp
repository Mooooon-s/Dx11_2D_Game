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
	}
	enums::eBTState PlayAnimaion::Run()
	{
		
		GameObject* gameObj = _BlackBoard->GetData<GameObject>(L"Guppy");
		Animator* at = gameObj->GetComponent<Animator>();
		enums::eBehavior behavior = _BlackBoard->GetDataValue<eBehavior>(L"Behavior");
		
		if (!at->AnimationComplete()&& _Behavior== behavior)
			return enums::eBTState::SUCCESS;


		enums::eFishState state = _BlackBoard->GetDataValue<eFishState>(L"Fish_State");
		
		
		switch (state)
		{
		case eFishState::Full:
			FullAnimaton(behavior);
			break;
		case eFishState::Starving:
			break;
		case eFishState::Death:
			break;
		default:
			break;
		}

		
		enums::eDir dir = _BlackBoard->GetDataValue<enums::eDir>(L"Dir");
		ConstantBuffer* cb = renderer::constantBuffer[(UINT)eCBType::Flip];
		renderer::FlipCB data = {};
		if (dir == eDir::Right)
			data.FlipX = 1;
		else
			data.FlipX = 0;
		cb->setData(&data);
		cb->Bind(eShaderStage::PS);

		return enums::eBTState::SUCCESS;
	}
	void PlayAnimaion::FullAnimaton(enums::eBehavior behavior)
	{
		GameObject* gameObj = _BlackBoard->GetData<GameObject>(L"Guppy");
		Animator* at = gameObj->GetComponent<Animator>();

		int level = _BlackBoard->GetDataValue<float>(L"Level");



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
					at->PlayAnimation(L"Turn_Small_Revers", false);
				}
				else
					at->PlayAnimation(L"Turn_Small", false);
				break;
			case 2:
				if (_BlackBoard->GetDataValue<eDir>(L"Dir") == eDir::Right)
					at->PlayAnimation(L"Turn_Middle_Revers", false);
				else
					at->PlayAnimation(L"Turn_Middle", false);
				break;
			case 3:
				if (_BlackBoard->GetDataValue<eDir>(L"Dir") == eDir::Right)
					at->PlayAnimation(L"Turn_Large_Revers", false);
				else
					at->PlayAnimation(L"Turn_Large", false);
				break;
			default:
				break;
			}
			break;
		case eBehavior::Eat:
			break;
		case eBehavior::End:
			break;
		default:
			break;
		}
	}
}
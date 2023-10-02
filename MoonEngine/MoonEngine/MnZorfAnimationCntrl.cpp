#include "MnZorfAnimationCntrl.h"
#include "MnGameObject.h"
#include "MnAnimator.h"

namespace Mn
{
	ZorfAnimationCntrl::ZorfAnimationCntrl()
		: _BlackBoard(nullptr)
	{
	}
	ZorfAnimationCntrl::ZorfAnimationCntrl(BlackBoard* board)
		: _BlackBoard(board)
	{
	}
	ZorfAnimationCntrl::~ZorfAnimationCntrl()
	{
	}
	enums::eBTState ZorfAnimationCntrl::Run()
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
	void ZorfAnimationCntrl::PlayAnimation(enums::eBehavior behavior)
	{
		GameObject* gameObj = _BlackBoard->GetData<GameObject>(L"Owner");
		Animator* at = gameObj->GetComponent<Animator>();
		eDir dir = _BlackBoard->GetDataValue<eDir>(L"Dir");

		switch (behavior)
		{
		case Mn::enums::eBehavior::Swim:
			at->PlayAnimation(L"Zorf_Swim", true);
			break;
		case Mn::enums::eBehavior::Turn:
			if (dir == eDir::Left)
				at->PlayAnimation(L"Zorf_Turn", true);
			else
				at->PlayAnimation(L"Zorf_Turn_Reverse", true);
			break;
		case Mn::enums::eBehavior::Feed:
			at->PlayAnimation(L"Zorf_Feed", true);
			break;
		}
	}
}
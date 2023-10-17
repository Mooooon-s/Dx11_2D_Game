#include "MnGusAnimatorCntrl.h"
#include "MnGameObject.h"
#include "MnAnimator.h"

namespace Mn
{
	GusAnimatorCntrl::GusAnimatorCntrl()
		: _BlackBoard(nullptr)
		, _Dir(eDir::Left)
	{
	}
	GusAnimatorCntrl::GusAnimatorCntrl(BlackBoard* board)
		: _BlackBoard(board)
		, _Dir(eDir::Left)
	{
	}
	GusAnimatorCntrl::~GusAnimatorCntrl()
	{
	}
	enums::eBTState GusAnimatorCntrl::Run()
	{
		GameObject* owner = _BlackBoard->GetData<GameObject>(L"Owner");
		eDir dir = _BlackBoard->GetDataValue<eDir>(L"Dir");
		Animator* at = owner->GetComponent<Animator>();

		if (!at->AnimationComplete() && _Dir != dir)
		{
			PlayAnimation();
			_Dir = dir;
			return enums::eBTState::SUCCESS;
		}
		else if (!at->AnimationComplete() && _Dir == dir)
			return enums::eBTState::SUCCESS;

		at->PlayAnimation(L"Gus_Swim",true);
		_Dir = dir;

		return enums::eBTState::SUCCESS;
	}
	void GusAnimatorCntrl::PlayAnimation()
	{
		GameObject* owner = _BlackBoard->GetData<GameObject>(L"Owner");
		eDir dir = _BlackBoard->GetDataValue<eDir>(L"Dir");
		Animator* at = owner->GetComponent<Animator>();

		if (dir == eDir::Left)
		{
			at->PlayAnimation(L"Gus_Turn_Reverse", true);
		}
		else
		{
			at->PlayAnimation(L"Gus_Turn", true);
		}
	}
}
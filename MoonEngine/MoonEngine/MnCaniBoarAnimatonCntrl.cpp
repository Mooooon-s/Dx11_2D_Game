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
		GameObject* owner = _BlackBoard->GetData<GameObject>(L"Owner");
		eDir dir = _BlackBoard->GetDataValue<eDir>(L"Dir");

		Animator* at = owner->GetComponent<Animator>();
		eFishState state = _BlackBoard->GetDataValue<eFishState>(L"Fish_State");

		switch (dir)
		{
		case eDir::Left:
			if (state == eFishState::Full || state == eFishState::Hungry)
				at->PlayAnimation(L"Caniboar_Turn",true);
			else
				at->PlayAnimation(L"Caniboar_Hungry_Turn", true);
			_BlackBoard->SetData(L"Dir", eDir::Right);
			break;
		case eDir::Right:
			if (state == eFishState::Full || state == eFishState::Hungry)
				at->PlayAnimation(L"Caniboar_Turn_Reverse", true);
			else
				at->PlayAnimation(L"Caniboar_Hungry_Turn_Reverse", true);
			_BlackBoard->SetData(L"Dir", eDir::Left);
			break;
		default:
			break;
		}

		_BlackBoard->SetData(L"Behavior", eBehavior::Swim);
		return enums::eBTState::SUCCESS;
	}
}
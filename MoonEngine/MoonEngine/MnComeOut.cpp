#include "MnComeOut.h"
#include "MnGameObject.h"
#include "MnAnimator.h"

namespace Mn
{
	ComeOut::ComeOut()
		: _BlackBoard(nullptr)
	{
	}
	ComeOut::ComeOut(BlackBoard* board)
		: _BlackBoard(board)
	{
	}
	ComeOut::~ComeOut()
	{
	}
	enums::eBTState ComeOut::Run()
	{
		if (_BlackBoard->GetDataValue<bool>(L"Hiding"))
		{
			GameObject* stinky = _BlackBoard->GetData<GameObject>(L"Owner");
			Animator* at = stinky->GetComponent<Animator>();
			at->PlayAnimation(L"Stinky_Hide_Reverse",true);
			_BlackBoard->SetData(L"Hiding", false);
			return enums::eBTState::SUCCESS;
		}
		return enums::eBTState::SUCCESS;
	}
}
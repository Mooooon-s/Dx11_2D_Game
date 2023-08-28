#include "MnStinkyHide.h"
#include "MnGameObject.h"
#include "MnAnimator.h"

namespace Mn
{
	StinkyHide::StinkyHide()
		: _BlackBoard(nullptr)
	{
	}
	StinkyHide::StinkyHide(BlackBoard* board)
		:_BlackBoard(board)
	{
	}
	StinkyHide::~StinkyHide()
	{
	}
	enums::eBTState StinkyHide::Run()
	{
		if (_BlackBoard->GetDataValue<bool>(L"Hiding")==false)
		{
			GameObject* stinky = _BlackBoard->GetData<GameObject>(L"Stinky");
			Animator* at = stinky->GetComponent<Animator>();
			enums::eDir dir = _BlackBoard->GetDataValue<enums::eDir>(L"Dir");
			at->PlayAnimation(L"Stinky_Hide",false);
			_BlackBoard->SetData(L"Hiding", true);
			return enums::eBTState::SUCCESS;
		}
		return enums::eBTState::SUCCESS;
	}
}
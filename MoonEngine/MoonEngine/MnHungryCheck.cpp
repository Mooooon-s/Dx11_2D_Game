#include "MnHungryCheck.h"
#include "MnGameObject.h"

namespace Mn
{
	HungryCheck::HungryCheck()
		:_BlackBoard(nullptr)
	{
	}
	HungryCheck::HungryCheck(BlackBoard* board)
		: _BlackBoard(board)
	{
	}
	HungryCheck::~HungryCheck()
	{
	}
	enums::eBTState HungryCheck::Run()
	{
		int hungrystack = _BlackBoard->GetDataValue<int>(L"HungryStack");
		if (hungrystack > 0)
		{
			_BlackBoard->SetData(L"Fish_State", eFishState::Full);
		}
		else if (hungrystack < 0 && hungrystack > -5)
		{
			_BlackBoard->SetData(L"Fish_State", eFishState::Hungry);
		}
		else if (hungrystack <= -5 && hungrystack > -10)
		{
			_BlackBoard->SetData(L"Fish_State", eFishState::Starving);
		}
		return enums::eBTState::SUCCESS;
	}
}
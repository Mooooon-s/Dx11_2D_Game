#include "MnIsHungry.h"

namespace Mn
{
	IsHungry::IsHungry()
	{
	}
	IsHungry::IsHungry(BlackBoard* board)
		:_BlackBoard(board)
	{
	}
	IsHungry::~IsHungry()
	{
	}
	enums::eBTState IsHungry::Run()
	{
		int stack = _BlackBoard->GetDataValue<int>(L"HungryStack");
		if (stack < 3)
		{
			_BlackBoard->SetData(L"Fish_State", enums::eFishState::Full);
			return enums::eBTState::FAILURE;
		}
		else if (stack >= 3 && stack <5 )
		{
			_BlackBoard->SetData(L"Fish_State", enums::eFishState::Hungry);
			return enums::eBTState::SUCCESS;
		}
		else if (stack >= 5)
		{
			_BlackBoard->SetData(L"Fish_State", enums::eFishState::Starving);
			return enums::eBTState::SUCCESS;
		}
		else
			return enums::eBTState::SUCCESS;
	}
}
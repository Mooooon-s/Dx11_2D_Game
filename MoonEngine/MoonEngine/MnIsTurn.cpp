#include "MnIsTurn.h"
#include "MnGameObject.h"
#include "MnAnimator.h"
#include <random>

namespace Mn
{
	IsTurn::IsTurn()
		:_BlackBoard(nullptr)
	{
	}
	IsTurn::IsTurn(BlackBoard* board)
		:_BlackBoard(board)
	{
	}
	int IsTurn::RandomInt()
	{
		srand((unsigned int)time(NULL));
		int random = rand();

		return (random % 2);
	}
	int IsTurn::Generate()
	{
		int x = RandomInt();
		int y = RandomInt();
		return (x&y);
	}
	enums::eBTState IsTurn::Run()
	{

		if (_BlackBoard->GetDataValue<float>(L"Timer")-_Time < 3)
			return enums::eBTState::FAILURE;

		if (Generate() == 0)
			return enums::eBTState::FAILURE;
		else
		{
			_Time = _BlackBoard->GetDataValue<float>(L"Timer");
			_BlackBoard->SetData(L"Behavior", enums::eBehavior::Turn);
			return enums::eBTState::SUCCESS;
		}
	}
}
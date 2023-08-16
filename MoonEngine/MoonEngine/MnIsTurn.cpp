#include "MnIsTurn.h"
#include "MnGameObject.h"
#include "MnAnimator.h"
#include <random>
#include "MnTime.h"

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
		srand(Time::DeltaTime());
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

		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_real_distribution<> dis(0.0, 1.0);

		double randomValue = dis(gen);

		// 15% probability of success
		if (randomValue <= 0.15) {
			_Time = _BlackBoard->GetDataValue<float>(L"Timer");
			_BlackBoard->SetData(L"Behavior", enums::eBehavior::Turn);
			return enums::eBTState::SUCCESS;
		}
		else {
			return enums::eBTState::FAILURE;
		}

	}
}
#include "MnFeedTimer.h"

namespace Mn
{
	FeedTimer::FeedTimer()
		: _BlackBoard(nullptr)
	{
	}
	FeedTimer::FeedTimer(BlackBoard* board)
		: _BlackBoard(board)
	{
	}
	FeedTimer::~FeedTimer()
	{
	}
	enums::eBTState FeedTimer::Run()
	{
		if (_BlackBoard->GetDataValue<bool>(L"FeedReady"))
			return enums::eBTState::SUCCESS;
		else
		{
			float time = _BlackBoard->GetDataValue<float>(L"Timer");
			float calcuTime = time - _Timer;
			if ((int)(calcuTime) % 2 == 0 && calcuTime != 0)
			{
				_BlackBoard->SetData(L"FeedReady", true);
			}
			_Timer = time;
		}
		return enums::eBTState::FAILURE;

	}
}
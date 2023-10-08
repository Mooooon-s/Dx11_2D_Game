#include "MnFeedTimer.h"

namespace Mn
{
	FeedTimer::FeedTimer()
		: _BlackBoard(nullptr)
		, _Timer(0.0f)
	{
	}
	FeedTimer::FeedTimer(BlackBoard* board)
		: _BlackBoard(board)
		, _Timer(0.0f)
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
			if ((int)(calcuTime) % 3 == 0 && calcuTime != 0)
			{
				_BlackBoard->SetData(L"FeedReady", true);
			}
			_Timer = time;
		}
		return enums::eBTState::FAILURE;
	}
}
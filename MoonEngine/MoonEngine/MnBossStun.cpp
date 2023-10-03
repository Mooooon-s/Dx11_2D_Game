#include "MnBossStun.h"

namespace Mn
{
	BossStun::BossStun()
		:_BlackBoard(nullptr)
	{
	}
	BossStun::BossStun(BlackBoard* board)
		: _BlackBoard(board)
	{
	}
	BossStun::~BossStun()
	{
	}
	enums::eBTState BossStun::Run()
	{
		float time = _BlackBoard->GetDataValue<float>(L"Timer");
		if (_BlackBoard->GetDataValue<bool>(L"GetDamege"))
		{
			float calculTime = time - _Time;
			if (calculTime >= 1.0)
			{
				_Time = time;
				_BlackBoard->SetData(L"GetDamege", false);
				_BlackBoard->ResetRunningNode();
				return enums::eBTState::SUCCESS;
			}
			else
			{
				_BlackBoard->SetRunningNode<BossStun>(this);
				return enums::eBTState::RUNNING;
			}
		}
		_Time = time;
		return enums::eBTState::SUCCESS;
	}
}
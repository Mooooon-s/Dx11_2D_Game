#include "MnRepeatUntilFail.h"
namespace Mn
{
	enums::eBTState RepeatUntilFail::Run()
	{
		enums::eBTState state;
		do {
			state = GetChildren()->Run();
			if (state == enums::eBTState::RUNNING)
				return enums::eBTState::RUNNING;
			if (state == enums::eBTState::FAILURE)
				return enums::eBTState::FAILURE;
		} while (state != enums::eBTState::FAILURE);
	}
}
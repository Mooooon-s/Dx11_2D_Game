#include "MnRepeatUntilFail.h"
namespace Mn
{
	enums::eBTState RepeatUntilFail::Run()
	{
		while (GetChildren()->Run() != enums::eBTState::FAILURE)
			return enums::eBTState::FAILURE;
	}
}
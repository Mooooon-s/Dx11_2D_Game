#include "MnSucceeder.h"
namespace Mn
{
	enums::eBTState Succeeder::Run()
	{
		if (GetChildren()->Run() == enums::eBTState::RUNNING)
			return enums::eBTState::RUNNING;
		return enums::eBTState::SUCCESS;
	}
}
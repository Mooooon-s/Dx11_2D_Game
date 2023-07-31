#include "MnInverter.h"
namespace Mn
{
	enums::eBTState Inverter::Run()
	{
		enums::eBTState state = GetChildren()->Run();
		if (state == enums::eBTState::RUNNING)
			return enums::eBTState::RUNNING;

		if (state == enums::eBTState::SUCCESS)
			return enums::eBTState::FAILURE;
		else
			return enums::eBTState::SUCCESS;
	}
}
#include "MnGetCharge.h"

namespace Mn
{
	GetCharge::GetCharge()
		: _BlackBoard(nullptr)
	{
	}
	GetCharge::GetCharge(BlackBoard* board)
		: _BlackBoard(board)
	{
	}
	GetCharge::~GetCharge()
	{
	}
	enums::eBTState GetCharge::Run()
	{
		float time = _BlackBoard->GetDataValue<float>(L"Timer");
		float unchargedtime = _BlackBoard->GetDataValue<float>(L"UnChargedTime");
		float calculatetime = time - unchargedtime;
		if (calculatetime >= 5.0)
		{
			_BlackBoard->SetData(L"Charged", true);
			return enums::eBTState::SUCCESS;
		}
		return enums::eBTState::FAILURE;
	}
}
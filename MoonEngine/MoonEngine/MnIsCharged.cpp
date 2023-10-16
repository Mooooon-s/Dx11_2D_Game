#include "MnIsCharged.h"

namespace Mn
{
	IsCharged::IsCharged()
		: _Blackboard(nullptr)
	{
	}
	IsCharged::IsCharged(BlackBoard* board)
		: _Blackboard(board)
	{
	}
	IsCharged::~IsCharged()
	{
	}
	enums::eBTState IsCharged::Run()
	{
		if (_Blackboard->GetDataValue<bool>(L"Charged"))
			return enums::eBTState::SUCCESS;
		else
			return enums::eBTState::FAILURE;
	}
}
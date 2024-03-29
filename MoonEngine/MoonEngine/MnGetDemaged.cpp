#include "MnGetDemaged.h"
#include "MnGameObject.h"

namespace Mn
{
	GetDemaged::GetDemaged()
		:_BlackBoard(nullptr)
	{
	}
	GetDemaged::GetDemaged(BlackBoard* board)
		:_BlackBoard(board)
	{
	}
	GetDemaged::~GetDemaged()
	{
	}
	enums::eBTState GetDemaged::Run()
	{
		int hp =_BlackBoard->GetDataValue<int>(L"Hp");
		hp -= 2;
		_BlackBoard->SetData(L"Hp", hp);
		return enums::eBTState::SUCCESS;
	}
}
#include "MnAddLevel.h"
#include "MnGameObject.h"

namespace Mn
{
	AddLevel::AddLevel()
		:_BlackBoard(nullptr)
	{
	}
	AddLevel::AddLevel(BlackBoard* board)
		:_BlackBoard(board)
	{
	}
	AddLevel::~AddLevel()
	{
	}
	enums::eBTState AddLevel::Run()
	{
		UINT stack = _BlackBoard->GetDataValue<UINT>(L"Level_Stack");
		UINT level = _BlackBoard->GetDataValue<float>(L"Level");

		switch (level)
		{
		case 1:
			if (stack >= 3)
			{
				_BlackBoard->SetData(L"Level_Stack", 0);
				_BlackBoard->SetData(L"Level", (float)2);
			}
			break;
		case 2:
			if (stack >= 3)
			{
				_BlackBoard->SetData(L"Level_Stack", 0);
				_BlackBoard->SetData(L"Level", (float)3);
			}
			break;
		case 3:
			if (stack >= 3)
			{
				_BlackBoard->SetData(L"Level_Stack", 0);
			}
			break;
		default:
			break;
		}

		return enums::eBTState::SUCCESS;
	}
}
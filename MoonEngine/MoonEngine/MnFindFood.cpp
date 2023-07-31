#include "MnFindFood.h"
#include "MnGameObject.h"

namespace Mn
{
	FindFood::FindFood()
		:_BlackBoard(nullptr)
	{
	}
	FindFood::FindFood(BlackBoard* blakcboard)
		:_BlackBoard(blakcboard)
	{
	}
	FindFood::~FindFood()
	{
	}
	enums::eBTState FindFood::Run()
	{
		if (_BlackBoard->GetData<GameObject*>(L"Food") != nullptr)
			return enums::eBTState::SUCCESS;
		return enums::eBTState::FAILURE;
	}
}
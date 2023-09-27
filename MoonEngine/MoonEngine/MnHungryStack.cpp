#include "MnHungryStack.h"

namespace Mn
{
	HungryStack::HungryStack()
		: _BlackBoard(nullptr)
	{
	}
	HungryStack::HungryStack(BlackBoard* board)
		: _BlackBoard(board)
	{
	}
	HungryStack::~HungryStack()
	{
	}
	enums::eBTState HungryStack::Run()
	{
		float time = _BlackBoard->GetDataValue<float>(L"Timer");

		if ((int)time % 3 == 0 && (int)time != 0)
		{
			int hungrystack = _BlackBoard->GetDataValue<int>(L"HungryStack");
			hungrystack -= 1;
			_BlackBoard->SetData(L"HungryStack", hungrystack);
		}
		return enums::eBTState::SUCCESS;
	}
}
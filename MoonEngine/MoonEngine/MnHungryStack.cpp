#include "MnHungryStack.h"
#include "MnGameObject.h"

namespace Mn
{
	HungryStack::HungryStack()
		: _BlackBoard(nullptr)
		, _Time(0.0f)
	{
	}
	HungryStack::HungryStack(BlackBoard* board)
		: _BlackBoard(board)
		, _Time(0.0f)
	{
	}
	HungryStack::~HungryStack()
	{
	}
	enums::eBTState HungryStack::Run()
	{
		float time = _BlackBoard->GetDataValue<float>(L"Timer");
		UINT flag = _BlackBoard->GetDataValue<UINT>(L"StackFlag");

		float afterTime = time - _Time;

		if ((int)afterTime % 3 == 0 && (int)afterTime != 0)
		{
			int hungrystack = _BlackBoard->GetDataValue<int>(L"HungryStack");
			hungrystack -= 1;
			_BlackBoard->SetData(L"HungryStack", hungrystack);
			_Time = time;
		}
		return enums::eBTState::SUCCESS;
	}
}
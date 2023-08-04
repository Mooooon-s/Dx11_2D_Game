#include "MnAddHungryStack.h"
#include "MnTime.h"
namespace Mn
{
	AddHungryStack::AddHungryStack()
	{
	}
	AddHungryStack::AddHungryStack(BlackBoard* board)
		: _BlackBoard(board)
		, _Time(0)
	{
	}
	AddHungryStack::~AddHungryStack()
	{
		
	}
	enums::eBTState AddHungryStack::Run()
	{
		_Time = _BlackBoard->GetDataValue<float>(L"Timer");
		
		if (_Time >= 3.0)
		{
			int stack = _BlackBoard->GetDataValue<int>(L"HungryStack");
			stack += 1;
			_BlackBoard->SetData(L"HungryStack", stack);
			_BlackBoard->SetData<float>(L"Timer",0);
		}
		return enums::eBTState::SUCCESS;
	}
}
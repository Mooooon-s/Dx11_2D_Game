#include "MnGuppyDeath.h"
#include "MnGameObject.h"
#include "MnAnimator.h"
#include "MnPlayAnimaion.h"

namespace Mn
{
	GuppyDeath::GuppyDeath()
		:_BlackBoard(nullptr)
	{
	}
	GuppyDeath::GuppyDeath(BlackBoard* board)
		:_BlackBoard(board)
	{
	}
	GuppyDeath::~GuppyDeath()
	{
	}
	enums::eBTState GuppyDeath::Run()
	{
		//애니메이션을 death로 변경
		int stack = _BlackBoard->GetDataValue<int>(L"HungryStack");
		if (stack > 7)
		{
			GameObject* obj = _BlackBoard->GetData<GameObject>(L"Guppy");
			eFishState state = _BlackBoard->GetDataValue<eFishState>(L"Fish_State");
			if (state != eFishState::Death)
			{
				_BlackBoard->SetData(L"Fish_State", eFishState::Death);
				PlayAnimaion* anima = new PlayAnimaion(_BlackBoard);
				anima->Run();
				return enums::eBTState::SUCCESS;
			}
			return enums::eBTState::SUCCESS;
		}
		return enums::eBTState::FAILURE;
	}
}
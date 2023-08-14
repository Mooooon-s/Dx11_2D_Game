#include "MnGuppyDeath.h"
#include "MnGameObject.h"
#include "MnAnimator.h"

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

		//음...애매한데 
		//좀더 생각하기
		int stack = _BlackBoard->GetDataValue<int>(L"HungryStack");
		if (stack > 7)
		{
			GameObject* obj = _BlackBoard->GetData<GameObject>(L"Guppy");
			eFishState state = _BlackBoard->GetDataValue<eFishState>(L"Fish_State");
			if (state != eFishState::Death)
			{

			}

			obj->State(GameObject::eState::Dead);
			return enums::eBTState::FAILURE;
		}
		return enums::eBTState::SUCCESS;
	}
}
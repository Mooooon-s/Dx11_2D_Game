#include "MnGuppyTurn.h"
#include "MnGameObject.h"
#include "MnAnimator.h"
#include "MnConstantBuffer.h"
#include "MnRenderer.h"
#include "MnPlayAnimaion.h"

namespace Mn
{
	GuppyTurn::GuppyTurn()
		: _Blackboard(nullptr)
	{
	}
	GuppyTurn::GuppyTurn(BlackBoard* board)
		: _Blackboard(board)
	{
	}
	enums::eBTState GuppyTurn::Run()
	{
		GameObject* gameObj = _Blackboard->GetData<GameObject>(L"Owner");
		Animator* at = gameObj->GetComponent<Animator>();

		PlayAnimaion* anima = new PlayAnimaion(_Blackboard);

		if (at->AnimationComplete())
		{
			enums::eDir dir = _Blackboard->GetDataValue<enums::eDir>(L"Dir");
			if (dir == enums::eDir::Left)
				_Blackboard->SetData<enums::eDir>(L"Dir", enums::eDir::Right);
			else
				_Blackboard->SetData<enums::eDir>(L"Dir", enums::eDir::Left);

			_Blackboard->SetData(L"Behavior", enums::eBehavior::Swim);
			anima->Run();
			_Blackboard->ResetRunningNode();
			return enums::eBTState::SUCCESS;
		}
		else
		{
			_Blackboard->SetRunningNode<GuppyTurn>(this);
			return enums::eBTState::RUNNING;
		}
	}
}
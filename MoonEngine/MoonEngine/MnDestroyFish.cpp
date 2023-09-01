#include "MnDestroyFish.h"
#include "MnGameObject.h"
#include "MnAnimator.h"

namespace Mn
{
	DestroyFish::DestroyFish()
		:_BlackBoard(nullptr)
	{
	}
	DestroyFish::DestroyFish(BlackBoard* board)
		: _BlackBoard(board)
	{
	}
	DestroyFish::~DestroyFish()
	{
	}
	enums::eBTState DestroyFish::Run()
	{
		GameObject* owner = _BlackBoard->GetData<GameObject>(L"Owner");
		Animator* at = owner->GetComponent<Animator>();
		if (at->AnimationComplete())
		{
			owner->State(GameObject::eState::Dead);
			return enums::eBTState::FAILURE;
		}
		else
		{
			_BlackBoard->SetRunningNode(this);
			return enums::eBTState::RUNNING;
		}
		return enums::eBTState::SUCCESS;
	}
}
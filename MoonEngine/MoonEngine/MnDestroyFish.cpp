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
		GameObject* guppy = _BlackBoard->GetData<GameObject>(L"Guppy");
		Animator* at = guppy->GetComponent<Animator>();
		if (at->AnimationComplete() == true)
		{
			guppy->State(GameObject::eState::Dead);
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
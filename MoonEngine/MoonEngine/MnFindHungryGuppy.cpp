#include "MnFindHungryGuppy.h"
#include "MnSceneManager.h"
#include "MnGuppy.h"

namespace Mn
{
	FindHungryGuppy::FindHungryGuppy()
		: _BlackBoard(nullptr)
	{
	}
	FindHungryGuppy::FindHungryGuppy(BlackBoard* board)
		: _BlackBoard(board)
	{
	}
	FindHungryGuppy::~FindHungryGuppy()
	{
	}
	enums::eBTState FindHungryGuppy::Run()
	{
		Scene* scene = SceneManager::ActiveScene();
		std::vector<GameObject*> gameobj = scene->GetLayer(eLayerType::Fish).GetGameObjects();
		for (auto obj : gameobj)
		{
			if (dynamic_cast<Guppy*>(obj))
				if (dynamic_cast<Guppy*>(obj)->FishStarving())
					return enums::eBTState::SUCCESS;
		}
		return enums::eBTState::FAILURE;
	}
}
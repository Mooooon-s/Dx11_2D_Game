#include "MnFindSmallGuppy.h"
#include "MnSceneManager.h"
#include "MnGuppy.h"

namespace Mn
{
	FindSmallGuppy::FindSmallGuppy()
		: _BlackBoard(nullptr)
	{
	}
	FindSmallGuppy::FindSmallGuppy(BlackBoard* board)
		: _BlackBoard(board)
	{
	}
	FindSmallGuppy::~FindSmallGuppy()
	{
	}
	enums::eBTState FindSmallGuppy::Run()
	{
		Scene* scene =SceneManager::ActiveScene();

		GameObject* owner = _BlackBoard->GetData<GameObject>(L"Owner");
		std::vector<GameObject*> fish = scene->GetLayer(eLayerType::Fish).GetGameObjects();
		for (auto f : fish)
		{
			if (dynamic_cast<Guppy*>(f))
			{
				Guppy* g = dynamic_cast<Guppy*>(f);
				if (g->FishLevel() == 1)
					return enums::eBTState::SUCCESS;
			}
		}
		return enums::eBTState::FAILURE;
	}
}
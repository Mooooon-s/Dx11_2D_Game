#include "MnFindBoss.h"

#include "MnSceneManager.h"
#include "MnGameObject.h"

namespace Mn
{
	FindBoss::FindBoss()
		: _BlackBoard(nullptr)
	{
	}
	FindBoss::FindBoss(BlackBoard* board)
		: _BlackBoard(board)
	{
	}
	FindBoss::~FindBoss()
	{
	}
	enums::eBTState FindBoss::Run()
	{
		Scene* scene = SceneManager::ActiveScene();
		std::vector<GameObject*> boss = scene->GetLayer(eLayerType::Monster).GetGameObjects();
		if (boss.size() == 0)
			return enums::eBTState::FAILURE;
		else
			return enums::eBTState::SUCCESS;
	}
}
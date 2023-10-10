#include "MnDetectBoss.h"
#include "MnSceneManager.h"
#include "MnGameObject.h"

namespace Mn
{
	DetectBoss::DetectBoss()
	{
	}
	DetectBoss::DetectBoss(BlackBoard* board)
	{
	}
	DetectBoss::~DetectBoss()
	{
	}
	enums::eBTState DetectBoss::Run()
	{
		Scene* scene = SceneManager::ActiveScene();
		std::vector<GameObject*> bossObj = scene->GetLayer(eLayerType::Monster).GetGameObjects();
		if (bossObj.size())
			return enums::eBTState::SUCCESS;
		return enums::eBTState::FAILURE;
	}
}
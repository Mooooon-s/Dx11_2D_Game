#include "MnGetBossPosition.h"
#include "MnSceneManager.h"

namespace Mn
{
	GetBossPosition::GetBossPosition()
		: _BlackBoard(nullptr)
	{
	}
	GetBossPosition::GetBossPosition(BlackBoard* board)
		: _BlackBoard(board)
	{
	}
	GetBossPosition::~GetBossPosition()
	{
	}
	enums::eBTState GetBossPosition::Run()
	{
		Scene* scene = SceneManager::ActiveScene();
		std::vector<GameObject*> bossObj = scene->GetLayer(eLayerType::Monster).GetGameObjects();
		
		if (bossObj.size()==0)
			return enums::eBTState::FAILURE;

		Vector3 bossPos = bossObj[0]->GetComponent<Transform>()->Position();
		_BlackBoard->SetData(L"BossPos", bossPos);
		return enums::eBTState::SUCCESS;
	}
}
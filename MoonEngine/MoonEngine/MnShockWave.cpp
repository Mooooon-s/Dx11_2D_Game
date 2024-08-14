#include "MnShockWave.h"
#include "MnSceneManager.h"
#include "MnSoundManager.h"
#include "MnGuppy.h"
#include "MnDiamond.h"
#include "MnObject.h"
#include "MnSparkEffect.h"

namespace Mn
{
	ShockWave::ShockWave()
		: _BlackBoard(nullptr)
	{
	}
	ShockWave::ShockWave(BlackBoard* board)
		: _BlackBoard(board)
	{
	}
	ShockWave::~ShockWave()
	{
	}
	enums::eBTState ShockWave::Run()
	{
		Scene* scene = SceneManager::ActiveScene();
		std::vector<GameObject*> fishObj = scene->GetLayer(eLayerType::Fish).GetGameObjects();
		for (auto obj : fishObj)
		{
			if (dynamic_cast<Guppy*>(obj))
			{
				Transform* tr = dynamic_cast<Guppy*>(obj)->GetComponent<Transform>();
				Vector3 pos = tr->Position();
				pos.z += 0.0001;
				SparkEffect* SE = object::Instantiate<SparkEffect>(pos, eLayerType::Effect);
				SE->Initialize();
				pos.z += 0.0001;
				Diamond* diamond = object::Instantiate<Diamond>(pos, eLayerType::Coin);
				diamond->Initialize();
				dynamic_cast<Guppy*>(obj)->State(GameObject::eState::Dead);
			}
		}
		_BlackBoard->SetData(L"Charged", false);
		_BlackBoard->SetData(L"UnChargedTime", _BlackBoard->GetDataValue<float>(L"Timer"));
		MnSoundManager::SoundPlay(L"ShockWave");
		return enums::eBTState::SUCCESS;
	}
}
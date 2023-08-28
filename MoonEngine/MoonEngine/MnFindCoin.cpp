#include "MnFindCoin.h"
#include "MnSceneManager.h"

namespace Mn
{
	FindCoin::FindCoin()
		:_BlackBoard(nullptr)
	{
	}
	FindCoin::FindCoin(BlackBoard* board)
		: _BlackBoard(board)
		, _NearestDistance(Vector3(999.0f, 999.0f, 999.0f))
	{
	}
	FindCoin::~FindCoin()
	{
	}
	enums::eBTState FindCoin::Run()
	{
		Scene* scene = SceneManager::ActiveScene();
		std::vector<GameObject*> gameObj = scene->GetLayer(eLayerType::Coin).GetGameObjects();
		if (gameObj.size() == 0)
			return enums::eBTState::FAILURE;
		else
		{
			ResetDistance();
			NearestCoin(gameObj);
			if (_NearestDistance.x >= 999.0f && _NearestDistance.y >= 999.0f)
				return enums::eBTState::FAILURE;
			return enums::eBTState::SUCCESS;
		}

	}
	void FindCoin::NearestCoin(std::vector<GameObject*> coin)
	{
		GameObject* stinky = _BlackBoard->GetData<GameObject>(L"Stinky");
		Vector3 pos = stinky->GetComponent<Transform>()->Position();
		pos.z = 0;
		for (auto obj : coin)
		{
			Transform* tr = obj->GetComponent<Transform>();
			Vector3 objPos = tr->Position();
			objPos.z = 0;
			Vector3 distance = objPos - pos;
			if (distance.x < _NearestDistance.x && distance.y < _NearestDistance.y)
			{
				_NearestDistance = distance;
			}
		}
		_BlackBoard->SetData(L"Nearest_Distance", _NearestDistance);
	}
}
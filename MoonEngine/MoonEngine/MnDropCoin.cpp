#include "MnDropCoin.h"
#include "MnCoin.h"
#include "MnGameObject.h"
#include "MnObject.h"

namespace Mn
{
	DropCoin::DropCoin()
		:_BlackBoard(nullptr)
	{
	}
	DropCoin::DropCoin(BlackBoard* board)
		:_BlackBoard(board)
	{
	}
	DropCoin::~DropCoin()
	{
	}
	enums::eBTState DropCoin::Run()
	{
		float timer = _BlackBoard->GetDataValue<float>(L"Timer");
		GameObject* owner = _BlackBoard->GetData<GameObject>(L"Owner");
		float level = _BlackBoard->GetDataValue<float>(L"Level");
		if ((int)timer % 3 == 0 && level>1)
		{
			Transform* tr = owner->GetComponent<Transform>();
			Vector3 pos = tr->Position();
			pos.z += 2.001;
			Coin* coin =object::Instantiate<Coin>(pos,enums::eLayerType::Coin);
			coin->SetLevel(level);
			coin->Initialize();
		}
		return enums::eBTState::SUCCESS;
	}
}
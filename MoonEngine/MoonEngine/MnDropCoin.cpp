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
		float time = _BlackBoard->GetDataValue<float>(L"Timer");
		float afterTime = time - _Time;
		GameObject* owner = _BlackBoard->GetData<GameObject>(L"Owner");
		UINT level = _BlackBoard->GetDataValue<UINT>(L"Level");
		if ((int)afterTime % 3 == 0 && level>1 && (int)afterTime!=0)
		{
			Transform* tr = owner->GetComponent<Transform>();
			Vector3 pos = tr->Position();
			pos.z += 2.001;
			Coin* coin =object::Instantiate<Coin>(pos,enums::eLayerType::Coin);
			coin->SetLevel(level);
			coin->Initialize();
			_Time = time;
		}
		return enums::eBTState::SUCCESS;
	}
}
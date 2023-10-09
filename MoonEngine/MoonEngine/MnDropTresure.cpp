#include "MnDropTresure.h"
#include "MnGameObject.h"
#include "MnCoin.h"
#include "MnObject.h"

namespace Mn
{
	DropTresure::DropTresure()
		: _BlackBoard(nullptr)
		, _ZPositon(6.0f)
	{
	}
	DropTresure::DropTresure(BlackBoard* board)
		: _BlackBoard(board)
		, _ZPositon(6.0f)
	{
	}
	DropTresure::~DropTresure()
	{
	}
	enums::eBTState DropTresure::Run()
	{
		UINT flag = _BlackBoard->GetDataValue<UINT>(L"StackFlag");
		GameObject* owner = _BlackBoard->GetData<GameObject>(L"Owner");

		if (flag)
		{
			Transform* tr = owner->GetComponent<Transform>();
			Vector3 pos = tr->Position();
			pos.z = _ZPositon;
			Coin* money = object::Instantiate<Coin>(pos, eLayerType::Coin);
			money->SetLevel(4);
			money->Initialize();
			_ZPositon += 0.000000001;
			_BlackBoard->SetData(L"StackFlag", 0);
		}
		return enums::eBTState::SUCCESS;
	}
}
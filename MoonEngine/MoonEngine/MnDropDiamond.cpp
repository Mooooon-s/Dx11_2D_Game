#include "MnDropDiamond.h"
#include "MnGameObject.h"
#include "MnObject.h"
#include "MnDiamond.h"


namespace Mn
{
	DropDiamond::DropDiamond()
		: _BlackBoard(nullptr)
		, _ZPositon(3.0f)
	{
	}
	DropDiamond::DropDiamond(BlackBoard* board)
		: _BlackBoard(board)
		, _ZPositon(3.0f)
	{
	}
	DropDiamond::~DropDiamond()
	{
	}
	enums::eBTState DropDiamond::Run()
	{
		UINT flag = _BlackBoard->GetDataValue<UINT>(L"StackFlag");
		GameObject* owner = _BlackBoard->GetData<GameObject>(L"Owner");

		if (flag)
		{
			Transform* tr = owner->GetComponent<Transform>();
			Vector3 pos = tr->Position();
			pos.z += 7.001;
			Diamond* diamond = object::Instantiate<Diamond>(pos, eLayerType::Coin);
			diamond->Initialize();
			_ZPositon += 0.000001;
			_BlackBoard->SetData(L"StackFlag", 0);
		}
		return enums::eBTState::SUCCESS;
	}
}
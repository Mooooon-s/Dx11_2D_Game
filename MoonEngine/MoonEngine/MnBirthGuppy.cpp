#include "MnBirthGuppy.h"
#include "MnGuppy.h"
#include "MnObject.h"
#include "MnGameObject.h"

namespace Mn
{
	BirthGuppy::BirthGuppy()
		: _BlackBoard(nullptr)
		, _ZPosition(0.0001f)
	{
	}
	BirthGuppy::BirthGuppy(BlackBoard* board)
		: _BlackBoard(board)
		, _ZPosition(0.001f)
	{
	}
	BirthGuppy::~BirthGuppy()
	{
	}
	enums::eBTState BirthGuppy::Run()
	{
		GameObject* owner = _BlackBoard->GetData<GameObject>(L"Owner");
		Transform* tr = owner->GetComponent<Transform>();
		Vector3 pos = tr->Position();
		pos.z += _ZPosition;
		_ZPosition += 0.0001;

		Guppy* guppy = object::Instantiate<Guppy>(pos , eLayerType::Fish);
		guppy->Initialize();

		return enums::eBTState::SUCCESS;
	}
}
#include "MnMove2Fish.h"
#include "MnGameObject.h"
#include "MnTime.h"

namespace Mn
{
	Move2Fish::Move2Fish()
		: _BlackBoard(nullptr)
	{
	}
	Move2Fish::Move2Fish(BlackBoard* board)
		: _BlackBoard(board)
	{
	}
	Move2Fish::~Move2Fish()
	{
	}
	enums::eBTState Move2Fish::Run()
	{
		Vector3 targetPos =_BlackBoard->GetDataValue<Vector3>(L"Target_Pos");
		GameObject* boss = _BlackBoard->GetData<GameObject>(L"Balrog");
		Transform* tr = boss->GetComponent<Transform>();
		Vector3 pos = tr->Position();
		pos.z = 0;
		Vector3 Vec = targetPos - pos;
		Vec.Normalize();
		pos += Vec * 0.2 * Time::DeltaTime();
		tr->Position(pos);
		return enums::eBTState();
	}
}
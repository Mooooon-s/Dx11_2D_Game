#include "MnTurn2Target.h"
#include "MnGameObject.h"

namespace Mn
{
	Turn2Target::Turn2Target()
		: _BlackBoard(nullptr)
	{
	}
	Turn2Target::Turn2Target(BlackBoard* board)
		: _BlackBoard(board)
	{
	}
	Turn2Target::~Turn2Target()
	{
	}
	enums::eBTState Turn2Target::Run()
	{
		GameObject* owner = _BlackBoard->GetData<GameObject>(L"Owner");
		Vector3 foodPos = _BlackBoard->GetDataValue<Vector3>(L"Food_Pos");

		if (foodPos == owner->GetComponent<Transform>()->Position())
			Turn2Fish();
		else
			Turn2Food();

		return enums::eBTState::SUCCESS;
	}
	void Turn2Target::Turn2Fish()
	{
		float moveSpeed = _BlackBoard->GetDataValue<float>(L"MoveSpeed");
		GameObject* owner = _BlackBoard->GetData<GameObject>(L"Owner");
		Vector3 Pos = owner->GetComponent<Transform>()->Position();
		Vector3 fishPos = _BlackBoard->GetDataValue<Vector3>(L"Target_Pos");
		eDir dir = _BlackBoard->GetDataValue<eDir>(L"Dir");

		Vector3 MoveVec = fishPos - Pos;
		if (dir == eDir::Left && MoveVec.x > 0)
			_BlackBoard->SetData(L"Dir", eDir::Right);
		else if (dir == eDir::Right && MoveVec.x < 0)
			_BlackBoard->SetData(L"Dir", eDir::Left);
	}
	void Turn2Target::Turn2Food()
	{
		float moveSpeed = _BlackBoard->GetDataValue<float>(L"MoveSpeed");
		GameObject* owner = _BlackBoard->GetData<GameObject>(L"Owner");
		Vector3 Pos = owner->GetComponent<Transform>()->Position();
		Vector3 foodPos = _BlackBoard->GetDataValue<Vector3>(L"Food_Pos");
		eDir dir = _BlackBoard->GetDataValue<eDir>(L"Dir");

		Vector3 MoveVec = foodPos - Pos;
		if (dir == eDir::Left && MoveVec.x > 0)
			_BlackBoard->SetData(L"Dir", eDir::Right);
		else if (dir == eDir::Right && MoveVec.x < 0)
			_BlackBoard->SetData(L"Dir", eDir::Left);
	}
}
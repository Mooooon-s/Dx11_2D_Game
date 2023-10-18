#include "MnMove2Target.h"
#include "MnGameObject.h"
#include "MnTime.h"

namespace Mn
{
	Move2Target::Move2Target()
		: _BlackBoard(nullptr)
	{
	}
	Move2Target::Move2Target(BlackBoard* board)
		: _BlackBoard(board)
	{
	}
	Move2Target::~Move2Target()
	{
	}
	enums::eBTState Move2Target::Run()
	{
		GameObject* owner = _BlackBoard->GetData<GameObject>(L"Owner");
		Vector3 foodPos = _BlackBoard->GetDataValue<Vector3>(L"Food_Pos");

		if (foodPos == owner->GetComponent<Transform>()->Position())
			Move2Fish();
		else
			Move2Food();
		return enums::eBTState::SUCCESS;
	}
	void Move2Target::Move2Food()
	{
		float moveSpeed = _BlackBoard->GetDataValue<float>(L"MoveSpeed");
		GameObject* owner = _BlackBoard->GetData<GameObject>(L"Owner");
		Vector3 Pos = owner->GetComponent<Transform>()->Position();
		Vector3 foodPos = _BlackBoard->GetDataValue<Vector3>(L"Food_Pos");

		Vector3 MoveVec = foodPos - Pos;
		MoveVec.z = 0.0f;
		MoveVec.Normalize();
		Pos += MoveVec * moveSpeed * Time::DeltaTime();
		Transform* tr = owner->GetComponent<Transform>();
		tr->Position(Pos);
	}
	void Move2Target::Move2Fish()
	{
		float moveSpeed = _BlackBoard->GetDataValue<float>(L"MoveSpeed");
		GameObject* owner = _BlackBoard->GetData<GameObject>(L"Owner");
		Vector3 Pos = owner->GetComponent<Transform>()->Position();
		Vector3 fishPos = _BlackBoard->GetDataValue<Vector3>(L"Target_Pos");

		Vector3 MoveVec = fishPos - Pos;
		MoveVec.Normalize();
		Pos += MoveVec * moveSpeed *Time::DeltaTime();
		Transform* tr = owner->GetComponent<Transform>();
		tr->Position(Pos);
	}
}
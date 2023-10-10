#include "MnRush2Boss.h"
#include "MnGameObject.h"
#include "MnTime.h"

namespace Mn
{
	Rush2Boss::Rush2Boss()
		: _BlackBoard(nullptr)
		, _Time(0.0f)
	{
	}
	Rush2Boss::Rush2Boss(BlackBoard* board)
		: _BlackBoard(board)
		, _Time(0.0f)
	{
	}
	Rush2Boss::~Rush2Boss()
	{
	}
	enums::eBTState Rush2Boss::Run()
	{
		_Time += Time::DeltaTime();
		if (_Time <= 1.5f)
		{
			Rush();
			_BlackBoard->SetRunningNode<Rush2Boss>(this);
			return enums::eBTState::RUNNING;
		}
		else
		{
			_Time = 0.0f;
			_BlackBoard->ResetRunningNode();
			return enums::eBTState::FAILURE;
		}
	}
	void Rush2Boss::Rush()
	{
		GameObject* owner = _BlackBoard->GetData<GameObject>(L"Owner");
		Vector3 pos = owner->GetComponent<Transform>()->Position();
		Vector3 bosspos = _BlackBoard->GetDataValue<Vector3>(L"BossPos");

		Vector3 moveVec = bosspos - pos;
		moveVec.z = 0;
		float norm = sqrtf(pow(moveVec.x, 2) + pow(moveVec.y, 2) + pow(moveVec.z, 2));
		moveVec = Vector3(moveVec.x / norm, moveVec.y / norm, moveVec.z / norm);
		pos += moveVec * 2 * Time::DeltaTime();
		owner->GetComponent<Transform>()->Position(pos);
	}
}
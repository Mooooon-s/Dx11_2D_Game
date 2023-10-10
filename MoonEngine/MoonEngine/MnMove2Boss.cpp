#include "MnMove2Boss.h"
#include "MnGameObject.h"
#include "MnTime.h"
#include "MnGetBossPosition.h"


namespace Mn
{
	Move2Boss::Move2Boss()
		: _BlackBoard(nullptr)
	{
	}
	Move2Boss::Move2Boss(BlackBoard* board)
		: _BlackBoard(board)
	{
	}
	Move2Boss::~Move2Boss()
	{
	}
	enums::eBTState Move2Boss::Run()
	{
		GameObject* owner = _BlackBoard->GetData<GameObject>(L"Owner");

		Vector3 pos = owner->GetComponent<Transform>()->Position();
		Vector3 bosspos = _BlackBoard->GetDataValue<Vector3>(L"BossPos");

		Vector3 vec = bosspos - pos;
		vec.z = 0;
		float distance = sqrtf(pow(vec.x, 2) + pow(vec.y, 2));
		if (distance <= 0.5)
		{
			_BlackBoard->ResetRunningNode();
			return enums::eBTState::SUCCESS;
		}
		else
		{
			vec.Normalize();
			pos += Vector3(vec.x, vec.y, 0.0f) * 2 * Time::DeltaTime();
			owner->GetComponent<Transform>()->Position(pos);
			_BlackBoard->SetRunningNode(_BlackBoard->GetData<GetBossPosition>(L"GetBossPosNode"));
			return enums::eBTState::RUNNING;
		}
	}
}
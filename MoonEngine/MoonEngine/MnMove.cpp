#include "MnMove.h"
#include "MnAnimator.h"
#include "MnGameObject.h"
#include "MnTransform.h"
#include "MnTime.h"
#include <random>

namespace Mn
{
	Move::Move()
		:_Blackboard(nullptr)
		, _Time(0)
		, _Speed(0.0f)
	{
	}
	Move::Move(BlackBoard* blackboard)
		:_Blackboard(blackboard)
		, _Time(0)
		, _Speed(0.0f)
	{
	}
	enums::eBTState Move::Run()
	{
		_Time += Time::DeltaTime();
		GameObject* owner = _Blackboard->GetData<GameObject>(L"Owner");
		_Speed = _Blackboard->GetDataValue<float>(L"MoveSpeed");
		eDir dir = _Blackboard->GetDataValue<eDir>(L"Dir");
		Transform* tr =owner->GetComponent<Transform>();
		Vector3 pos = tr->Position();

		//std::random_device rd;
		//std::mt19937 gen(rd());
		//std::uniform_real_distribution<> dis(0.0, 3.0);

		//double randomValue = dis(gen);


		if (_Time <= 1.0f)
		{
			if (dir == eDir::Left)
			{
				if(pos.x > -2.2f)
					pos+= Vector3(-1.0f, 0.05f, 0.0f) * _Speed * Time::DeltaTime();
				else
					pos+= Vector3(1.0f, 0.05f, 0.0f) * _Speed * Time::DeltaTime();

				if(pos.y> 1.0f)
					pos+= Vector3(0.0f, -0.05f, 0.0f) * _Speed * Time::DeltaTime();
			}
			else
			{
				if(pos.x<2.2)
					pos += Vector3(1.0f, 0.05f, 0.0f) * _Speed * Time::DeltaTime();
				else
					pos += Vector3(-1.0f, 0.05f, 0.0f) * _Speed * Time::DeltaTime();

				if (pos.y > 1.0f)
					pos += Vector3(0.0f, -0.05f, 0.0f) * _Speed * Time::DeltaTime();
			}
			tr->Position(pos);
			_Blackboard->SetRunningNode<Move>(this);
			return enums::eBTState::RUNNING;
		}
		else
		{
			_Time = 0.0f;
			_Blackboard->ResetRunningNode();
			return enums::eBTState::SUCCESS;
		}
		return enums::eBTState::SUCCESS;
	}
}
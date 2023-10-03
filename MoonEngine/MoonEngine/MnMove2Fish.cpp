#include "MnMove2Fish.h"
#include "MnGameObject.h"
#include "MnAnimator.h"
#include "MnTime.h"

namespace Mn
{
	Move2Fish::Move2Fish()
		: _BlackBoard(nullptr)
		, _Count(0)
	{
	}
	Move2Fish::Move2Fish(BlackBoard* board)
		: _BlackBoard(board)
		, _Count(0)
	{
	}
	Move2Fish::~Move2Fish()
	{
	}
	enums::eBTState Move2Fish::Run()
	{
		GameObject* boss = _BlackBoard->GetData<GameObject>(L"Balrog");
		Transform* tr = boss->GetComponent<Transform>();
		eDir dir = _BlackBoard->GetDataValue<eDir>(L"Dir");

		bool hunting = _BlackBoard->GetDataValue<bool>(L"GetDamege");
		if (hunting)
		{
			Vector3 mousePos = _BlackBoard->GetDataValue<Vector3>(L"MousePos");
			Vector3 pos = tr->Position();
			Vector3 Vec = mousePos - pos;
			
			if (Vec.x > 0)
			{
				//마우스가 오른쪽
				if (dir == eDir::Right)
				{
					Animator* at =boss->GetComponent<Animator>();
					at->PlayAnimation(L"Balrog_Turn_Left", true);
					_BlackBoard->SetData(L"Dir", eDir::Left);
				}
			}
			else
			{
				//마우스가 왼쪽
				if (dir == eDir::Left)
				{
					Animator* at = boss->GetComponent<Animator>();
					at->PlayAnimation(L"Balrog_Turn_Right", true);
					_BlackBoard->SetData(L"Dir", eDir::Right);
				}
			}
			float time = _BlackBoard->GetDataValue<float>(L"Timer");
			float calculTime = time - _Time;
			if (calculTime >= 1.0)
			{
				_Time = time;
				_BlackBoard->SetData(L"GetDamege", false);
				_BlackBoard->ResetRunningNode();
				return enums::eBTState::SUCCESS;
			}
			else
			{
				_BlackBoard->SetRunningNode<Move2Fish>(this);
				return enums::eBTState::RUNNING;
			}

			//Vec.Normalize();
			//pos += Vec * -1 * 0.5 * Time::DeltaTime();
			//tr->Position(pos);

		}
		else
		{
			Vector3 targetPos = _BlackBoard->GetDataValue<Vector3>(L"Target_Pos");
			Vector3 pos = tr->Position();
			pos.z = 0;
			Vector3 Vec = targetPos - pos;
			Vec.Normalize();
			pos += Vec * 0.2 * Time::DeltaTime();
			tr->Position(pos);

			if (Vec.x  > 0 && dir == eDir::Left)
			{
				Animator* at = boss->GetComponent<Animator>();
				at->PlayAnimation(L"Balrog_Turn_Right", true);
				_BlackBoard->SetData(L"Dir", eDir::Right);
			}
			else if (Vec.x < 0 && dir == eDir::Right)
			{
				Animator* at = boss->GetComponent<Animator>();
				at->PlayAnimation(L"Balrog_Turn_Left", true);
				_BlackBoard->SetData(L"Dir", eDir::Left);
			}

		}
		return enums::eBTState::SUCCESS;
	}
}
#include "MnMove2Fish.h"
#include "MnGameObject.h"
#include "MnAnimator.h"
#include "MnTime.h"

#include "MnMonIsDead.h"

namespace Mn
{
	Move2Fish::Move2Fish()
		: _BlackBoard(nullptr)
		, _Count(0)
		, _Time(0.0f)
	{
	}
	Move2Fish::Move2Fish(BlackBoard* board)
		: _BlackBoard(board)
		, _Count(0)
		, _Time(0.0f)
	{
	}
	Move2Fish::~Move2Fish()
	{
	}
	enums::eBTState Move2Fish::Run()
	{
		GameObject* boss = _BlackBoard->GetData<GameObject>(L"Owner");
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
					at->PlayAnimation(AnimationName(), true);
					_BlackBoard->SetData(L"Dir", eDir::Left);
				}
			}
			else
			{
				//마우스가 왼쪽
				if (dir == eDir::Left)
				{
					Animator* at = boss->GetComponent<Animator>();
					at->PlayAnimation(AnimationName(), true);
					_BlackBoard->SetData(L"Dir", eDir::Right);
				}
			}
			_Time = _BlackBoard->GetDataValue<float>(L"StunTime");

			if (_Time >= 1.0)
			{
				_Time = 0;
				_BlackBoard->SetData(L"StunTime", _Time);
				_BlackBoard->SetData(L"GetDamege", false);
				_BlackBoard->ResetRunningNode();
				return enums::eBTState::SUCCESS;
			}
			else
			{
				_Time += Time::DeltaTime();
				_BlackBoard->SetData(L"StunTime", _Time);
				Vec.Normalize();
				pos += Vec * -1 * 0.5 * Time::DeltaTime();
				tr->Position(pos);
				SetRunningNode();
				return enums::eBTState::RUNNING;
			}
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
				at->PlayAnimation(AnimationName(), true);
				_BlackBoard->SetData(L"Dir", eDir::Right);
			}
			else if (Vec.x < 0 && dir == eDir::Right)
			{
				Animator* at = boss->GetComponent<Animator>();
				at->PlayAnimation(AnimationName(), true);
				_BlackBoard->SetData(L"Dir", eDir::Left);
			}
		}
		return enums::eBTState::SUCCESS;
	}
	void Move2Fish::SetRunningNode()
	{
		MonIsDead* dead = _BlackBoard->GetData<MonIsDead>(L"IsDeadNode");
		_BlackBoard->SetRunningNode<MonIsDead>(dead);
	}
	std::wstring Move2Fish::AnimationName()
	{
		std::wstring boss;
		eBossType type = _BlackBoard->GetDataValue<eBossType>(L"BossType");
		eDir dir = _BlackBoard->GetDataValue<eDir>(L"Dir");
		switch (type)
		{
		case Mn::enums::eBossType::Barlog:
			boss = L"Balrog";
			break;
		case Mn::enums::eBossType::Sylv:
			boss = L"Sylv";
			break;
		case Mn::enums::eBossType::End:
			break;
		default:
			break;
		}
		if (dir == eDir::Left)
			boss += L"_Turn_Right";
		else
			boss += L"_Turn_Left";
		return boss;
	}
}
#include "MnSwim.h"
#include "MnGameObject.h"
#include "MnTime.h"
namespace Mn
{
	Swim::Swim()
		: _BlackBoard(nullptr)
		, _Speed(0.0f)
	{
	}
	Swim::Swim(BlackBoard* board)
		: _BlackBoard(board)
		, _Speed(3.0f)
	{
	}
	Swim::~Swim()
	{
	}
	enums::eBTState Swim::Run()
	{
		GameObject* owner = _BlackBoard->GetData<GameObject>(L"Owner");
		Transform* tr = owner->GetComponent<Transform>();

		enums::eDir dir = _BlackBoard->GetDataValue<enums::eDir>(L"Dir");

		Vector3 pos = tr->Position();

		if (dir == eDir::Left)
		{
			if (pos.x > -2.2f)
				pos += Vector3(-1.0f, 0.05f, 0.0f) * _Speed * Time::DeltaTime();
			else
				pos += Vector3(1.0f, 0.05f, 0.0f) * _Speed * Time::DeltaTime();

			if (pos.y > 1.0f)
				pos += Vector3(0.0f, -0.05f, 0.0f) * _Speed * Time::DeltaTime();
		}
		else
		{
			if (pos.x < 2.2)
				pos += Vector3(1.0f, 0.05f, 0.0f) * _Speed * Time::DeltaTime();
			else
				pos += Vector3(-1.0f, 0.05f, 0.0f) * _Speed * Time::DeltaTime();

			if (pos.y > 1.0f)
				pos += Vector3(0.0f, -0.05f, 0.0f) * _Speed * Time::DeltaTime();
		}
		tr->Position(pos);
		return enums::eBTState::SUCCESS;
	}
}
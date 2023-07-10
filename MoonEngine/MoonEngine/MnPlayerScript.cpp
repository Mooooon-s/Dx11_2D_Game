#include "MnPlayerScript.h"
#include "MnTransform.h"
#include "MnInput.h"
#include "MnTime.h"
#include "MnGameObject.h"

Mn::PlayerScript::PlayerScript()
{
}

Mn::PlayerScript::~PlayerScript()
{
}

void Mn::PlayerScript::Update()
{
	Transform* tr = GetOwner()->GetComponent<Transform>();
	Vector3 pos = tr->Position();

	if (Input::GetKey(eKeyCode::W))
	{
		pos.z += 5.0f * Time::DeltaTime();
		tr->Position(pos);
	}
	else if (Input::GetKey(eKeyCode::S))
	{
		pos.z -= 5.0f * Time::DeltaTime();
		tr->Position(pos);
	}
	else if (Input::GetKey(eKeyCode::A))
	{
		pos.x -= 5.0f * Time::DeltaTime();
		tr->Position(pos);
	}
	else if (Input::GetKey(eKeyCode::D))
	{
		pos.x += 5.0f * Time::DeltaTime();
		tr->Position(pos);
	}
	else if (Input::GetKey(eKeyCode::Q))
	{
		pos.y -= 5.0f * Time::DeltaTime();
		tr->Position(pos);
	}
	else if (Input::GetKey(eKeyCode::E))
	{
		pos.y += 5.0f * Time::DeltaTime();
		tr->Position(pos);
	}
}

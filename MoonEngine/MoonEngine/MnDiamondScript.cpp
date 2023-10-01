#include "MnDiamondScript.h"
#include "MnTime.h"

namespace Mn
{
	DiamondScript::DiamondScript()
		: _Speed(0.3f)
		, _Time(0.0f)
	{
	}
	DiamondScript::~DiamondScript()
	{
	}
	void DiamondScript::Initialize()
	{
	}
	void DiamondScript::Update()
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector3 pos = tr->Position();
		pos += Vector3(0.0f, -1.0f, 0.0f) * _Speed * Time::DeltaTime();
		tr->Position(pos);

	}
	void DiamondScript::LateUpdate()
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector3 pos = tr->Position();
		if (pos.y <= -1.3f)
		{
			_Time += Time::DeltaTime();
			if (_Time >= 0.5)
			{
				GetOwner()->State(GameObject::eState::Dead);
			}
		}
	}
	void DiamondScript::Render()
	{
	}
}
#include "MnFoodScript.h"
#include "MnGameObject.h"
#include "MnTime.h"

namespace Mn
{
	FoodScript::FoodScript()
		: _Speed(0.3f)
		, _Alpha(1.0f)
	{
	}
	FoodScript::~FoodScript()
	{
	}
	void FoodScript::Initialize()
	{
	}
	void FoodScript::Update()
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector3 pos = tr->Position();
		if(tr->Position().y >= -1.3f)
			pos += Vector3(0.0f, -1.0f, 0.0f) * _Speed * Time::DeltaTime();
		else
		{
			MeshRenderer* mr = GetOwner()->GetComponent<MeshRenderer>();
			_Alpha -= 0.8f * Time::DeltaTime();
			mr->AlphaValue(_Alpha);
		}
		tr->Position(pos);
	}
	void FoodScript::LateUpdate()
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();
		if (tr->Position().y <= -1.0f)
		{
			if(_Alpha<=0.0f)
				GetOwner()->State(GameObject::eState::Dead);
		}
	}
	void FoodScript::Render()
	{
	}
}
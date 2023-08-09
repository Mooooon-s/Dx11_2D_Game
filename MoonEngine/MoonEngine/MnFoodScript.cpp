#include "MnFoodScript.h"
#include "MnGameObject.h"
#include "MnTime.h"

namespace Mn
{
	FoodScript::FoodScript()
		: _Speed(0.3f)
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
		pos += Vector3(0.0f, -1.0f, 0.0f) * _Speed * Time::DeltaTime();
		tr->Position(pos);
		Script::Update();
	}
	void FoodScript::LateUpdate()
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();
		if (tr->Position().y <= -1.0f)
			GetOwner()->State(GameObject::eState::Dead);
		Script::LateUpdate();
	}
	void FoodScript::Render()
	{
		Script::Render();
	}
}
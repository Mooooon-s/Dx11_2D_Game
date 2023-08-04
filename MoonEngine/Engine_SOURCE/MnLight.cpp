#include "MnLight.h"
#include "MnRenderer.h"
#include "MnTransform.h"
#include "MnGameObject.h"

namespace Mn
{
	Light::Light()
		:Component(enums::eComponentType::Light)
	{
	}
	Light::~Light()
	{
	}
	void Light::Initialize()
	{
	}
	void Light::Update()
	{
	}
	void Light::LateUpdate()
	{
		renderer::lights.push_back(this);

		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector3 pos = tr->Position();
		_Attribute.position = Vector4(pos.x, pos.y, pos.z, 1.0f);
		_Attribute.direction = Vector4(tr->Foward().x, tr->Foward().y, tr->Foward().z, 1.0f);
	}
	void Light::Render()
	{
	}
}
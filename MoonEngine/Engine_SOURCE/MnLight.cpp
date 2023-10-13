#include "MnLight.h"
#include "MnRenderer.h"
#include "MnTransform.h"
#include "MnGameObject.h"

namespace Mn
{
	Light::Light()
		:Component(enums::eComponentType::Light)
		, _SceneName(L"000")
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
		if (_SceneName != L"000")
			renderer::Lights.insert(std::make_pair(_SceneName, this));
		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector3 pos = tr->Position();
		_Attribute.position = Vector4(pos.x, pos.y, pos.z, 1.0f);
		_Attribute.direction = Vector4(tr->Foward().x, tr->Foward().y, tr->Foward().z, 1.0f);
	}
	void Light::Render()
	{
	}
}
#include "MnTransform.h"
#include "MnRenderer.h"
#include "MnConstantBuffer.h"

namespace Mn
{
	using namespace Mn::graphics;
	Transform::Transform()
		: Component(eComponentType::Transform)
		, _Position(Vector3::Zero)
		, _Rotation(Vector3::Zero)
		, _Scale(Vector3::One)
	{
	}
	Transform::~Transform()
	{
	}
	void Transform::Initialize()
	{
	}
	void Transform::Update()
	{
	}
	void Transform::LateUpdate()
	{
	}
	void Transform::Render()
	{
	}
	void Transform::BindConstantBuffer()
	{
		ConstantBuffer* cb = renderer::constantBuffer;
		Vector4 position(_Position.x, _Position.y, _Position.z, 1.0f);
		cb->setData(&position);
		cb->Bind(eShaderStage::VS);
	}
}
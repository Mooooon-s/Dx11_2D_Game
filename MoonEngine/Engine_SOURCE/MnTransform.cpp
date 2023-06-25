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
		_World = Matrix::Identity;
		Matrix scale = Matrix::CreateScale(_Scale);

		Matrix rotation;
		rotation = Matrix::CreateRotationX(_Rotation.x);
		rotation *= Matrix::CreateRotationY(_Rotation.y);
		rotation *= Matrix::CreateRotationZ(_Rotation.z);

		Matrix position;
		position.Translation(_Position);

		_World = scale * rotation * position;
		_Up = Vector3::TransformNormal(Vector3::Up, rotation);
		_Forward = Vector3::TransformNormal(Vector3::Forward, rotation);
		_Right = Vector3::TransformNormal(Vector3::Right, rotation);
	}
	void Transform::Render()
	{
	}
	void Transform::BindConstantBuffer()
	{
		renderer::TransformCB trCB = {};
		trCB._World = _World;
		trCB._View = Camera::GetViewMatrix();
		trCB._Projection = Camera::GetProjectionMatrix();
		ConstantBuffer* cb = renderer::constantBuffer[(UINT)eCBType::Transform];
		//Vector4 position(_Position.x, _Position.y, _Position.z, 1.0f);
		cb->setData(&trCB);
		cb->Bind(eShaderStage::VS);
	}
}
#include "MnTransform.h"
#include "MnRenderer.h"
#include "MnConstantBuffer.h"
#include "MnComponent.h"
#include "MnResources.h"
#include "MnGameObject.h"
#include "MnMeshRenderer.h"

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

		if (_Parent)
		{
			_World *= _Parent->_World;
		}
	}
	void Transform::Render()
	{
	}
	void Transform::BindConstantBuffer()
	{
		renderer::TransformCB trCB = {};
		trCB._World = _World;
		trCB._View = Camera::GetGpuViewMatrix();
		trCB._Projection = Camera::GetGpuProjectionMatrix();
		ConstantBuffer* cb = renderer::constantBuffer[(UINT)eCBType::Transform];
		cb->setData(&trCB);
		cb->Bind(eShaderStage::VS);
		cb->Bind(eShaderStage::HS);
		cb->Bind(eShaderStage::DS);
		cb->Bind(eShaderStage::GS);
		cb->Bind(eShaderStage::PS);
	}
}
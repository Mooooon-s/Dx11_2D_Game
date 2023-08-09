#include "MnCollider2D.h"
#include "MnGameObject.h"
#include "MnRenderer.h"

namespace Mn
{
	graphics::DebugMesh Collider2D::_DebugMesh = {};

	Collider2D::Collider2D()
		: Component(eComponentType::Collider2D)
		, _Transform(nullptr)
		, _Size(Vector2::One)
		, _Center(Vector2::Zero)
	{
	}
	Collider2D::~Collider2D()
	{
	}
	void Collider2D::Initialize()
	{
		_Transform = GetOwner()->GetComponent<Transform>();
	}
	void Collider2D::Update()
	{
	}
	void Collider2D::LateUpdate()
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();
		_Scale = tr->Scale();
		_Scale.x *= _Size.x;
		_Scale.y *= _Size.y;

		Vector3 pos = tr->Position();
		pos.x += _Center.x;
		pos.y += _Center.y;

		_Position = pos;

		//graphics::DebugMesh mesh = {};
		_DebugMesh.position = pos;
		_DebugMesh.scale = _Scale;
		_DebugMesh.rotation = tr->Rotation();
		_DebugMesh.type = eColliderType::Rect;

		renderer::PushDebugMeshAttribute(_DebugMesh);


	}
	void Collider2D::Render()
	{
		Vector4 intersect = Vector4::Zero;
		if (_stay)
			intersect = Vector4(1.0, 0.0, 0.0, 0.0);
		else
			intersect = Vector4(0.0, 0.0, 0.0, 0.0);
		ConstantBuffer* cb = renderer::constantBuffer[(UINT)eCBType::Debug];
		cb->setData(&intersect);
		cb->Bind(eShaderStage::PS);
	}
	void Collider2D::OnCollisionEnter(Collider2D* other)
	{
		const std::vector<Script*> scripts = GetOwner()->GetComponents<Script>();
		for (Script* script : scripts)
		{
			script->OnCollisionEnter(other);
		}
	}
	void Collider2D::OnCollisionStay(Collider2D* other)
	{



		const std::vector<Script*>& scripts = GetOwner()->GetComponents<Script>();

		for (Script* script : scripts)
		{
			script->OnCollisionStay(other);
		}
	}
	void Collider2D::OnCollisionExit(Collider2D* other)
	{
		const std::vector<Script*>& scripts = GetOwner()->GetComponents<Script>();

		for (Script* script : scripts)
		{
			script->OnCollisionExit(other);
		}
	
	}
	Vector3 Collider2D::HeightVector()
	{
		Vector3 h =GetOwner()->GetComponent<Transform>()->Up();
		Vector3 height = h* (_Scale.y / 2.0f);
		return height;
	}
	Vector3 Collider2D::WidthVector()
	{
		Vector3 w = GetOwner()->GetComponent<Transform>()->Right();
		Vector3 width = w * (_Scale.x / 2.0f);
		return width;
	}
}
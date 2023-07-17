#include "MnPumpkin.h"
#include "MnComponent.h"
#include "MnMeshRenderer.h"
#include "MnResources.h"
#include "MnTransform.h"
#include "MnCollider2D.h"

namespace Mn
{
	Pumpkin::Pumpkin()
	{
	}
	Pumpkin::~Pumpkin()
	{
	}
	void Pumpkin::Initialize()
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"MonMaterial"));
		Collider2D* coll = AddComponent<Collider2D>();
		GameObject::Initialize();
	}
	void Pumpkin::Update()
	{
		GameObject::Update();
	}
	void Pumpkin::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void Pumpkin::Render()
	{
		GameObject::Render();
	}
}
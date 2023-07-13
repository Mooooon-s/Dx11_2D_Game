#include "MnPumpkin.h"
#include "MnComponent.h"
#include "MnMeshRenderer.h"
#include "MnResources.h"
#include "MnTransform.h"

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
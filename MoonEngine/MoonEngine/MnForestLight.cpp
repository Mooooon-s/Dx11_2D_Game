#include "MnForestLight.h"

#include "MnMeshRenderer.h"
#include "MnResources.h"

namespace Mn
{
	ForestLight::ForestLight()
	{
	}
	ForestLight::~ForestLight()
	{
	}
	void ForestLight::Initialize()
	{
		SetName(L"background_Light");
		MeshRenderer* BGmr = AddComponent<MeshRenderer>();
		BGmr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		BGmr->SetMaterial(Resources::Find<Material>(L"BackGroundMaterial_Light"));
		BGmr->GetMaterial()->GetTexture()->CalculateRatio();
		Vector2 v = BGmr->GetMaterial()->GetTexture()->Raitio();
		GetComponent<Transform>()->Position(Vector3(0.0f, 0.0f, 2.7f));
		GetComponent<Transform>()->Scale(Vector3(v.x * 4.5, v.y * 4.5, 1.0f));
	}
	void ForestLight::Update()
	{
		GameObject::Update();
	}
	void ForestLight::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void ForestLight::Render()
	{
		GameObject::Render();
	}
}
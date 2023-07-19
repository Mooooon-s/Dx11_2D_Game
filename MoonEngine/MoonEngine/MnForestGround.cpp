#include "MnForestGround.h"
#include "MnMeshRenderer.h"
#include "MnResources.h"

namespace Mn
{
	ForestGround::ForestGround()
	{
	}
	ForestGround::~ForestGround()
	{
	}
	void ForestGround::Initialize()
	{
		SetName(L"background_Ground");
		MeshRenderer* BGmr = AddComponent<MeshRenderer>();
		BGmr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		BGmr->SetMaterial(Resources::Find<Material>(L"BackGround_forest_Ground"));
		BGmr->GetMaterial()->GetTexture()->CalculateRatio();
		Vector2 v = BGmr->GetMaterial()->GetTexture()->Raitio();
		GetComponent<Transform>()->Position(Vector3(0.0f, 0.0f, 2.6f));
		GetComponent<Transform>()->Scale(Vector3(v.x * 4.5, v.y * 4.5, 1.0f));
	}
	void ForestGround::Update()
	{
		GameObject::Update();
	}
	void ForestGround::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void ForestGround::Render()
	{
		GameObject::Render();
	}
}
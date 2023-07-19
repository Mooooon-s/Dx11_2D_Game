#include "MnCavePillar.h"
#include "MnResources.h"
#include "MnMeshRenderer.h"
#include "MnTransform.h"
#include "MnMesh.h"

namespace Mn
{
	CavePillar::CavePillar()
	{
	}
	CavePillar::~CavePillar()
	{
	}
	void CavePillar::Initialize()
	{
		MeshRenderer* BGmr = this->AddComponent<MeshRenderer>();
		BGmr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		BGmr->SetMaterial(Resources::Find<Material>(L"BackGround_Cave_BackGround_2"));
		BGmr->GetMaterial()->GetTexture()->CalculateRatio();
		Vector2 v = BGmr->GetMaterial()->GetTexture()->Raitio();
		this->GetComponent<Transform>()->Position(Vector3(0.0f, 0.0f, 2.8f));
		this->GetComponent<Transform>()->Scale(Vector3(v.x * 4.5, v.y * 4.5, 1.0f));
	}
	void CavePillar::Update()
	{
		GameObject::Update();
	}
	void CavePillar::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void CavePillar::Render()
	{
		GameObject::Render();
	}
}
#include "MnCaveBossBG.h"
#include "MnMeshRenderer.h"
#include "MnResources.h"

namespace Mn
{
	CaveBossBG::CaveBossBG()
	{
	}
	CaveBossBG::~CaveBossBG()
	{
	}
	void CaveBossBG::Initialize()
	{
		MeshRenderer* BGmr = this->AddComponent<MeshRenderer>();
		BGmr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		BGmr->SetMaterial(Resources::Find<Material>(L"BackGround_Cave_Rock_type_3"));
		BGmr->GetMaterial()->GetTexture()->CalculateRatio();
		Vector2 v = BGmr->GetMaterial()->GetTexture()->Raitio();
		this->GetComponent<Transform>()->Position(Vector3(0.0f, 0.0f, 2.5f));
		this->GetComponent<Transform>()->Scale(Vector3(v.x * 4.5, v.y * 4.5, 1.0f));
	}
	void CaveBossBG::Update()
	{
		GameObject::Update();
	}
	void CaveBossBG::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void CaveBossBG::Render()
	{
		GameObject::Render();
	}
}
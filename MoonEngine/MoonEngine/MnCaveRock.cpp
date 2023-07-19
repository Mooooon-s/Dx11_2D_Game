#include "MnCaveRock.h"
#include "MnMeshRenderer.h"
#include "MnResources.h"

namespace Mn
{
	CaveRock::CaveRock()
	{
	}
	CaveRock::~CaveRock()
	{
	}
	void CaveRock::Initialize()
	{
		MeshRenderer* BGmr = this->AddComponent<MeshRenderer>();
		BGmr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		BGmr->SetMaterial(Resources::Find<Material>(L"BackGround_Cave_Rock_type_1"));
		BGmr->GetMaterial()->GetTexture()->CalculateRatio();
		Vector2 v = BGmr->GetMaterial()->GetTexture()->Raitio();
		this->GetComponent<Transform>()->Position(Vector3(0.0f, 0.0f, 2.7f));
		this->GetComponent<Transform>()->Scale(Vector3(v.x * 4.5, v.y * 4.5, 1.0f));
	}
	void CaveRock::Update()
	{
		GameObject::Update();
	}
	void CaveRock::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void CaveRock::Render()
	{
		GameObject::Render();
	}
}
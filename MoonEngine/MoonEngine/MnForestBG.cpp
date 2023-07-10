#include "MnForestBG.h"
#include "MnMeshRenderer.h"
#include "MnTransform.h"
#include "MnResources.h"
#include "MnTexture.h"

namespace Mn
{
	ForestBG::ForestBG()
	{
	}
	ForestBG::~ForestBG()
	{
	}
	void ForestBG::Initialize()
	{
		MeshRenderer* BGmr = this->AddComponent<MeshRenderer>();
		BGmr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		BGmr->SetMaterial(Resources::Find<Material>(L"BackGroundMaterial_Layer_0"));
		BGmr->GetMaterial()->GetTexture()->CalculateRatio();
		Vector2 v = BGmr->GetMaterial()->GetTexture()->Raitio();
		this->GetComponent<Transform>()->Position(Vector3(0.0f, 0.0f, 2.0f));
		this->GetComponent<Transform>()->Scale(Vector3(v.x * 4.5, v.y * 4.5, 1.0f));
	}
	void ForestBG::Update()
	{
		GameObject::Update();
	}
	void ForestBG::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void ForestBG::Render()
	{
		Material* mat = GetComponent<Material>();
		mat->TextureBind(Resources::Find<Texture>(L"BackGroundMaterial_Layer_1"), 1);
		
		GameObject::Render();
	}
}
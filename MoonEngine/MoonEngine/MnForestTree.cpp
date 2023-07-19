#include "MnForestTree.h"
#include "MnMeshRenderer.h"
#include "MnResources.h"

namespace Mn
{
	ForestTree::ForestTree()
	{
	}
	ForestTree::~ForestTree()
	{
	}
	void ForestTree::Initialize()
	{
		MeshRenderer* BGmr = AddComponent<MeshRenderer>();
		BGmr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		BGmr->SetMaterial(Resources::Find<Material>(L"BackGroundMaterial_Tree"));
		BGmr->GetMaterial()->GetTexture()->CalculateRatio();
		Vector2 v = BGmr->GetMaterial()->GetTexture()->Raitio();
		GetComponent<Transform>()->Position(Vector3(0.0f, 0.0f, 2.8f));
		GetComponent<Transform>()->Scale(Vector3(v.x * 4.5, v.y * 4.5, 1.0f));
	}
	void ForestTree::Update()
	{
		GameObject::Update();
	}
	void ForestTree::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void ForestTree::Render()
	{
		GameObject::Render();
	}
}
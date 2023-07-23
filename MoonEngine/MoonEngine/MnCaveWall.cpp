#include "MnCaveWall.h"
#include "MnMeshRenderer.h"
#include "MnMesh.h"
#include "MnTransform.h"
#include "MnResources.h"

namespace Mn
{
	CaveWall::CaveWall()
	{
	}
	CaveWall::~CaveWall()
	{
	}
	void CaveWall::Initialize()
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"TestMaterial"));
		mr->GetMaterial()->GetTexture()->CalculateRatio();
		Vector2 v = mr->GetMaterial()->GetTexture()->Raitio();
		GetComponent<Transform>()->Position(Vector3(0.0f, 0.0f, 2.9f));
		GetComponent<Transform>()->Scale(Vector3(v.x * 4.5, v.y * 4.5, 1.0f));
	}
	void CaveWall::Update()
	{
		GameObject::Update();
	}
	void CaveWall::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void CaveWall::Render()
	{
		GameObject::Render();
	}
}
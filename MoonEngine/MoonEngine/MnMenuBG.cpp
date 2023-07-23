#include "MnMenuBG.h"
#include "MnMeshRenderer.h"
#include "MnResources.h"

namespace Mn
{
	MenuBG::MenuBG()
	{
	}
	MenuBG::~MenuBG()
	{
	}
	void MenuBG::Initialize()
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"Menu_Material"));
		Vector2 ratio = mr->GetMaterial()->GetTexture()->CalculateRatio();
		GetComponent<Transform>()->Position(Vector3(0.0f, 0.0f, 2.9f));
		GetComponent<Transform>()->Scale(Vector3(ratio.x * 3.6, ratio.y * 3.6, 1.0f));
	}
	void MenuBG::Update()
	{
		GameObject::Update();
	}
	void MenuBG::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void MenuBG::Render()
	{
		GameObject::Render();
	}
}
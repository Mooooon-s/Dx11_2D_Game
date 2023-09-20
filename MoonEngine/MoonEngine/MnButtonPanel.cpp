#include "MnButtonPanel.h"
#include "MnMeshRenderer.h"
#include "MnResources.h"

namespace Mn
{
	ButtonPanel::ButtonPanel()
	{
	}
	ButtonPanel::~ButtonPanel()
	{
	}
	void ButtonPanel::Initialize()
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"PanelMaterial"));
	}
	void ButtonPanel::Update()
	{
		GameObject::Update();
	}
	void ButtonPanel::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void ButtonPanel::Render()
	{
		GameObject::Render();
	}
	void ButtonPanel::OnClick()
	{
		int c = 0;
	}
	void ButtonPanel::MouseOn()
	{
		int a = 0;
	}
	void ButtonPanel::MouseOff()
	{
		int b = 0;
	}
}
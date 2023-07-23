#include "MnTopBar.h"
#include "MnMeshRenderer.h"
#include "MnResources.h"

namespace Mn
{
	TopBar::TopBar()
	{
	}
	TopBar::~TopBar()
	{
	}
	void TopBar::Initialize()
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"TopBar_Material"));
		Vector2 ratio = mr->GetMaterial()->GetTexture()->CalculateRatio();
		GetComponent<Transform>()->Position(Vector3(0.0f, 1.52f, 2.8f));
		GetComponent<Transform>()->Scale(Vector3(ratio.x * 0.56f, ratio.y * 0.56f, 1.0f));

		_AlphaTex = Resources::Load<Mn::graphics::Texture>(L"menubar_Alpha",L"..\\Resources\\Texture\\UI\\bar\\_menubar.jpg");
	}
	void TopBar::Update()
	{
		GameObject::Update();
	}
	void TopBar::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void TopBar::Render()
	{
		MeshRenderer* mr = GetComponent<MeshRenderer>();
		mr->GetMaterial()->TextureBind(_AlphaTex,1);
		GameObject::Render();
	}
}
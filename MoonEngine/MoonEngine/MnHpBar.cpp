#include "MnHpBar.h"
#include "MnMeshRenderer.h"
#include "MnResources.h"

namespace Mn
{
	HpBar::HpBar(Scene* scene)
		: _Scene(scene)
	{
	}
	HpBar::~HpBar()
	{
	}
	void HpBar::Initialize()
	{
		MeshRenderer* hpBarMr = AddComponent<MeshRenderer>();
		hpBarMr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		hpBarMr->SetMaterial(Resources::Find<Material>(L"HP_BAR_Back"));

		std::shared_ptr<Material> mt = hpBarMr->GetMaterial();
		Vector2 scale = mt->CalcurateRatio();
		Transform* tr = GetComponent<Transform>();
		tr->Scale(Vector3(scale.x * 0.25, scale.y * 0.25, 0.0f));
		tr->Position(Vector3(-3.0f, 2.0f, 0.2f));
	}
	void HpBar::Update()
	{
		GameObject::Update();
	}
	void HpBar::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void HpBar::Render()
	{
		GameObject::Render();
	}
}
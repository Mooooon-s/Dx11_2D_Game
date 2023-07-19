#include "MnHpFrame.h"
#include "MnMeshRenderer.h"
#include "MnResources.h"

namespace Mn
{
	HpFrame::HpFrame(Scene* scene)
		: _Scene(scene)
	{
	}
	HpFrame::~HpFrame()
	{
	}
	void HpFrame::Initialize()
	{
		MeshRenderer* hpBarMr = AddComponent<MeshRenderer>();
		hpBarMr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		hpBarMr->SetMaterial(Resources::Find<Material>(L"HP_BAR_FRAME"));

		std::shared_ptr<Material> mt = hpBarMr->GetMaterial();
		Vector2 scale = mt->CalcurateRatio();
		Transform* tr = GetComponent<Transform>();
		//tr->Scale(Vector3(scale.x * 0.36, scale.y * 0.3, 0.0f));
		tr->Position(Vector3(0.0f, 0.0f, 0.0f));
	}
	void HpFrame::Update()
	{
		GameObject::Update();
	}
	void HpFrame::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void HpFrame::Render()
	{
		GameObject::Render();
	}
}
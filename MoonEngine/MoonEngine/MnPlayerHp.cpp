#include "MnPlayerHp.h"
#include "../Engine_SOURCE/MnMeshRenderer.h"
#include "../Engine_SOURCE/MnResources.h"
#include "../Engine_SOURCE/MnTransform.h"

namespace Mn
{
	PlayerHp::PlayerHp(Scene* scene)
		: _Scene(scene)
	{
	}
	PlayerHp::~PlayerHp()
	{
	}
	void PlayerHp::Initialize()
	{
		MeshRenderer* hpBarMr = AddComponent<MeshRenderer>();
		hpBarMr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		hpBarMr->SetMaterial(Resources::Find<Material>(L"HP_BAR_ProgressBar"));

		std::shared_ptr<Material> mt = hpBarMr->GetMaterial();
		Vector2 scale = mt->CalcurateRatio();
		Transform* tr = GetComponent<Transform>();
		tr->Scale(Vector3(scale.x*0.106f, scale.y*0.55f, 0.0f));
		tr->Position(Vector3(0.0f, 0.0f, 0.1f));
	}
	void PlayerHp::Update()
	{
		GameObject::Update();
	}
	void PlayerHp::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void PlayerHp::Render()
	{
		GameObject::Render();
	}
}
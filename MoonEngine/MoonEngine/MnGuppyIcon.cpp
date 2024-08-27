#include "MnGuppyIcon.h"

#include "MnAnimator.h"
#include "MnMeshRenderer.h"
#include "MnResources.h"

namespace Mn
{
	GuppyIcon::GuppyIcon()
	{
	}
	GuppyIcon::~GuppyIcon()
	{
	}
	void GuppyIcon::Initialize()
	{
		SetName(L"[Guppy]");
		Transform* tr = GetComponent<Transform>();
		tr->Scale(0.45f, 0.45f, 0.0f);
		Vector3 pos = tr->Position();
		pos.y += 0.05;
		tr->Position(pos);

		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"SpriteAnimaionMaterial"));
		mr->FlipX(0);

		std::shared_ptr<Mn::graphics::Texture> atlas
			= Resources::Find< Mn::graphics::Texture>(L"Guppy_Sprite");
		std::shared_ptr<Mn::graphics::Texture> atlasAlpha
			= Resources::Find<Mn::graphics::Texture>(L"Guppy_Sprite_Alpha");
		
		Animator* at = AddComponent<Animator>();
		at->Create(L"Guppy_Icon", atlas, atlasAlpha, Vector2(0.0f, 0.0f), Vector2(80.0f, 80.f), 10, Vector2::Zero, 0.1);

		at->PlayAnimation(L"Guppy_Icon", true);

	}
	void GuppyIcon::Update()
	{
		GameObject::Update();
	}
	void GuppyIcon::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void GuppyIcon::Render()
	{
		GameObject::Render();
	}
}
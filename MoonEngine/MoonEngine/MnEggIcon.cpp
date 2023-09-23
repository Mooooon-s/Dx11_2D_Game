#include "MnEggIcon.h"

#include "MnMeshRenderer.h"
#include "MnResources.h"
#include "MnAnimator.h"

namespace Mn
{
	EggIcon::EggIcon()
	{
	}
	EggIcon::~EggIcon()
	{
	}
	void EggIcon::Initialize()
	{
		Transform* tr = GetComponent<Transform>();
		tr->Scale(0.2f, 0.2f, 0.0f);
		Vector3 pos = tr->Position();
		pos.y += 0.05;
		tr->Position(pos);

		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"SpriteAnimaionMaterial"));
		mr->FlipX(0);

		std::shared_ptr<Mn::graphics::Texture> atlas
			= Resources::Load< Mn::graphics::Texture>(L"Egg_Icon_Sprite",L"..\\Resources\\Texture\\Item\\Egg\\EggPieces.jpg");
		std::shared_ptr<Mn::graphics::Texture> atlasAlpha
			= Resources::Load<Mn::graphics::Texture>(L"Egg_Icon_Sprite_Alpha",L"..\\Resources\\Texture\\Item\\Egg\\_EggPieces.jpg");

		Animator* at = AddComponent<Animator>();
		at->Create(L"Egg_Icon_1", atlas, atlasAlpha, Vector2(0.0f, 0.0f), Vector2(46.0f, 39.0f), 1, Vector2::Zero, 0.1);
		at->Create(L"Egg_Icon_2", atlas, atlasAlpha, Vector2(46.0f, 0.0f), Vector2(46.0f, 39.0f), 1, Vector2::Zero, 0.1);
		at->Create(L"Egg_Icon_3", atlas, atlasAlpha, Vector2(92.0f, 0.0f), Vector2(46.0f, 39.0f), 1, Vector2::Zero, 0.1);

		at->PlayAnimation(L"Egg_Icon_1", true);
	}
	void EggIcon::Update()
	{
		GameObject::Update();
	}
	void EggIcon::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void EggIcon::Render()
	{
		GameObject::Render();
	}
}
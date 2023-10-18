#include "MnPregoIcon.h"
#include "MnResources.h"
#include "MnAnimator.h"

namespace Mn
{
	PregoIcon::PregoIcon()
	{
	}
	PregoIcon::~PregoIcon()
	{
	}
	void PregoIcon::Initialize()
	{
		Transform* tr = GetComponent<Transform>();
		tr->Scale(Vector3(0.8, 0.8, 0.0f));
		Vector3 pos = tr->Position();
		pos.y += 0.05;
		tr->Position(pos);

		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"SpriteAnimaionMaterial"));
		mr->FlipX(0);

		std::shared_ptr<Mn::graphics::Texture> atlas
			= Resources::Load< Mn::graphics::Texture>(L"prego_Icon_Sprite", L"..\\Resources\\Texture\\Pet\\prego\\scl_prego.jpg");
		std::shared_ptr<Mn::graphics::Texture> atlasAlpha
			= Resources::Load<Mn::graphics::Texture>(L"prego_Icon_Sprite_Alpha", L"..\\Resources\\Texture\\Pet\\prego\\_scl_prego.jpg");

		Animator* at = AddComponent<Animator>();
		at->Create(L"Prego_Icon", atlas, atlasAlpha, Vector2(0.0f, 0.0f), Vector2(60.0f, 60.f), 10, Vector2::Zero, 0.1);

		at->PlayAnimation(L"Prego_Icon", true);
	}
	void PregoIcon::Update()
	{
		GameObject::Update();
	}
	void PregoIcon::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void PregoIcon::Render()
	{
		GameObject::Render();
	}
}
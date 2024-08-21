#include "MnUltravoreIcon.h"

#include "MnMeshRenderer.h"
#include "MnResources.h"
#include "MnAnimator.h"

namespace Mn
{
	UltravoreIcon::UltravoreIcon()
	{
	}
	UltravoreIcon::~UltravoreIcon()
	{
	}
	void UltravoreIcon::Initialize()
	{
		SetName(L"[Ultravore]");
		Transform* tr = GetComponent<Transform>();
		tr->Scale(0.25f, 0.25f, 0.0f);
		Vector3 pos = tr->Position();
		pos.y += 0.05;
		tr->Position(pos);

		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"SpriteAnimaionMaterial"));
		mr->FlipX(0);
		std::shared_ptr<Mn::graphics::Texture> atlas
			= Resources::Load< Mn::graphics::Texture>(L"Ultravore_Icon_Sprite", L"..\\Resources\\Texture\\Fish\\scl_ultra.jpg");
		std::shared_ptr<Mn::graphics::Texture> atlasAlpha
			= Resources::Load<Mn::graphics::Texture>(L"Ultravore_Icon_Sprite_Alpha", L"..\\Resources\\Texture\\Fish\\_scl_ultra.jpg");

		Animator* at = AddComponent<Animator>();
		at->Create(L"Ultravore_Icon", atlas, atlasAlpha, Vector2::Zero, Vector2(40, 40), 10, Vector2::Zero, 0.1f);
		at->PlayAnimation(L"Ultravore_Icon", true);

	}
	void UltravoreIcon::Update()
	{
		GameObject::Update();
	}
	void UltravoreIcon::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void UltravoreIcon::Render()
	{
		GameObject::Render();
	}
}
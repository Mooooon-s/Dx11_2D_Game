#include "MnCaniboarIcon.h"
#include "MnResources.h"
#include "MnAnimator.h"

namespace Mn
{
	CaniboarIcon::CaniboarIcon()
	{
	}

	CaniboarIcon::~CaniboarIcon()
	{
	}

	void CaniboarIcon::Initialize()
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
			= Resources::Load< Mn::graphics::Texture>(L"Caniboar_Icon_Sprite",L"..\\Resources\\Texture\\Fish\\scl_oscar.jpg");
		std::shared_ptr<Mn::graphics::Texture> atlasAlpha
			= Resources::Load<Mn::graphics::Texture>(L"Caniboar_Icon_Sprite_Alpha", L"..\\Resources\\Texture\\Fish\\_scl_oscar.jpg");

		Animator* at = AddComponent<Animator>();
		at->Create(L"Caniboar_Icon", atlas, atlasAlpha, Vector2::Zero, Vector2(40,40), 10, Vector2::Zero, 0.1f);
		at->PlayAnimation(L"Caniboar_Icon", true);

	}

	void CaniboarIcon::Update()
	{
		GameObject::Update();
	}

	void CaniboarIcon::LateUpdate()
	{
		GameObject::LateUpdate();
	}

	void CaniboarIcon::Render()
	{
		GameObject::Render();
	}
}
#include "MnNikoIcon.h"
#include "MnResources.h"
#include "MnAnimator.h"

namespace Mn
{
	NikoIcon::NikoIcon()
	{
	}
	NikoIcon::~NikoIcon()
	{
	}
	void NikoIcon::Initialize()
	{
		SetName(L"[Niko]");
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
			= Resources::Load< Mn::graphics::Texture>(L"Niko_Icon_Sprite",L"..\\Resources\\Texture\\Pet\\niko\\scl_niko.jpg");
		std::shared_ptr<Mn::graphics::Texture> atlasAlpha
			= Resources::Load<Mn::graphics::Texture>(L"Niko_Icon_Sprite_Alpha", L"..\\Resources\\Texture\\Pet\\niko\\_scl_niko.jpg");

		Animator* at = AddComponent<Animator>();
		at->Create(L"Niko_Icon", atlas, atlasAlpha, Vector2(0.0f, 0.0f), Vector2(60.0f, 60.f), 10, Vector2::Zero, 0.1);

		at->PlayAnimation(L"Niko_Icon", true);
	}
	void NikoIcon::Update()
	{
		GameObject::Update();
	}
	void NikoIcon::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void NikoIcon::Render()
	{
		GameObject::Render();
	}
}
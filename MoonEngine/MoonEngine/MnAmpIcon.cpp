#include "MnAmpIcon.h"
#include "MnResources.h"
#include "MnAnimator.h"

namespace Mn
{
	AmpIcon::AmpIcon()
	{
	}
	AmpIcon::~AmpIcon()
	{
	}
	void AmpIcon::Initialize()
	{
		Transform* tr = GetComponent<Transform>();
		tr->Scale(Vector3(1.0f, 0.5f, 0.0f));
		Vector3 pos = tr->Position();
		pos.y += 0.05;
		tr->Position(pos);

		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"SpriteAnimaionMaterial"));
		mr->FlipX(0);

		std::shared_ptr<Mn::graphics::Texture> atlas
			= Resources::Load< Mn::graphics::Texture>(L"Amp_Icon_Sprite", L"..\\Resources\\Texture\\Pet\\amp\\scl_amp.jpg");
		std::shared_ptr<Mn::graphics::Texture> atlasAlpha
			= Resources::Load<Mn::graphics::Texture>(L"Amp_Icon_Sprite_Alpha", L"..\\Resources\\Texture\\Pet\\amp\\_scl_amp.jpg");

		Animator* at = AddComponent<Animator>();
		at->Create(L"Amp_Icon", atlas, atlasAlpha, Vector2(0.0f, 0.0f), Vector2(64.0f, 24.f), 10, Vector2::Zero, 0.1);

		at->PlayAnimation(L"Amp_Icon", true);
	}
	void AmpIcon::Update()
	{
		GameObject::Update();
	}
	void AmpIcon::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void AmpIcon::Render()
	{
		GameObject::Render();
	}
}
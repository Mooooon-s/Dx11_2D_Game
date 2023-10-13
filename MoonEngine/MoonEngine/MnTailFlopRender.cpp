#include "MnTailFlopRender.h"
#include "MnResources.h"
#include "MnAnimator.h"
#include "MnGameObject.h"

namespace Mn
{
	TailFlopRender::TailFlopRender()
	{
	}
	TailFlopRender::~TailFlopRender()
	{
	}
	void TailFlopRender::Initialize()
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();
		tr->Scale(Vector3(1.65f, 0.5f, 0.0f));

		MeshRenderer* mr = GetOwner()->AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"TailSpriteAnimaionMaterial"));
		mr->FlipX(0);
		mr->AlphaValue(1);

		Animator* at = GetOwner()->AddComponent<Animator>();

		std::shared_ptr<Mn::graphics::Texture> atlas
			= Resources::Load<Mn::graphics::Texture>(L"Tail_Sprite", L"..\\Resources\\Texture\\UI\\etc\\tailflop.jpg");

		std::shared_ptr<Mn::graphics::Texture> atlasAlpha
			= Resources::Load<Mn::graphics::Texture>(L"Tail_Sprite_Alpha", L"..\\Resources\\Texture\\UI\\etc\\tailflop_.jpg");

		at->Create(L"Tail_Flop", atlas, atlasAlpha, Vector2::Zero, Vector2(238, 165), 8, Vector2::Zero, 0.1f);

		at->PlayAnimation(L"Tail_Flop", true);
	}
	void TailFlopRender::Update()
	{
	}
	void TailFlopRender::LateUpdate()
	{
	}
	void TailFlopRender::Render()
	{
	}
}
#include "MnNikoRenderer.h"
#include "MnTexture.h"
#include "MnResources.h"
#include "MnAnimator.h"
#include "MnMeshRenderer.h"
#include "MnMaterial.h"
#include "MnGameObject.h"

namespace Mn
{
	NikoRenderer::NikoRenderer()
	{
	}
	NikoRenderer::~NikoRenderer()
	{
	}
	void NikoRenderer::Initialize()
	{
		MeshRenderer* mr = GetOwner()->AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"SpriteAnimaionMaterial"));
		mr->FlipX(1);

		std::shared_ptr<Mn::graphics::Texture> atlas
			= Resources::Load<Mn::graphics::Texture>(L"Niko_Sprite", L"..\\Resources\\Texture\\Pet\\niko\\niko.jpg");
		std::shared_ptr<Mn::graphics::Texture> atlasAlpha
			= Resources::Load<Mn::graphics::Texture>(L"Niko_Sprite_Alpha", L"..\\Resources\\Texture\\Pet\\niko\\_niko.jpg");

		Animator* at = GetOwner()->AddComponent<Animator>();
		at->Create(L"Niko_Idle", atlas, atlasAlpha, Vector2(0.0f, 0.0f), Vector2(80.0f, 80.f), 10, Vector2::Zero, 0.1);
		at->Create(L"Niko_Open", atlas, atlasAlpha, Vector2(0.0f, 80.0f), Vector2(80.0f, 80.f), 10, Vector2::Zero, 0.1);
		at->CreateReverse(L"Niko_Close", atlas, atlasAlpha, Vector2(0.0f, 160.0f), Vector2(80.0f, 80.f), 10, Vector2::Zero, 0.1);

		at->CompleteEvent(L"Niko_Close") = std::bind(&NikoRenderer::AfterClick, this);

		at->PlayAnimation(L"Niko_Idle", true);
	}
	void NikoRenderer::Update()
	{
		MeshRenderer* mr = GetOwner()->GetComponent<MeshRenderer>();
		mr->FlipX(0);
	}
	void NikoRenderer::LateUpdate()
	{
	}
	void NikoRenderer::Render()
	{
	}
	void NikoRenderer::AfterClick()
	{
		Animator* at = GetOwner()->GetComponent<Animator>();
		at->PlayAnimation(L"Niko_Idle", true);
	}
}
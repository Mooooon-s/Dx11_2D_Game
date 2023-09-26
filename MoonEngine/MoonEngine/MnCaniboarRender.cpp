#include "MnCaniboarRender.h"
#include "MnResources.h"
#include "MnMeshRenderer.h"
#include "MnAnimator.h"
#include "MnGameObject.h"

namespace Mn
{
	CaniboarRender::CaniboarRender()
	{
	}
	CaniboarRender::~CaniboarRender()
	{
	}
	void CaniboarRender::Initialize()
	{
		MeshRenderer* mr = GetOwner()->AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"SpriteAnimaionMaterial"));
		Animator* at = GetOwner()->AddComponent<Animator>();

		std::shared_ptr<Mn::graphics::Texture> atlas = Resources::Find<Mn::graphics::Texture>(L"Guppy_Sprite");
		std::shared_ptr<Mn::graphics::Texture> atlasAlpha = Resources::Find<Mn::graphics::Texture>(L"Guppy_Sprite_Alpha");

		at->Create(L"Caniboar_Swim", atlas, atlasAlpha, Vector2(0.0f, 320.0f), Vector2(80.0f, 80.f), 10, Vector2::Zero, 0.1);

		atlas = Resources::Find<Mn::graphics::Texture>(L"Hungry_Guppy_Sprite");
		atlasAlpha = Resources::Find<Mn::graphics::Texture>(L"Hungry_Guppy_Sprite_Alpha");

		at->Create(L"Caniboar_Hungry_Swim", atlas, atlasAlpha, Vector2(0.0f, 320.0f), Vector2(80.0f, 80.f), 10, Vector2::Zero, 0.1);

		atlas = Resources::Find<Mn::graphics::Texture>(L"Guppy_Turn_Sprite");
		atlasAlpha = Resources::Find<Mn::graphics::Texture>(L"Guppy_Turn_Sprite_Alpha");

		at->Create(L"Caniboar_Turn", atlas, atlasAlpha, Vector2(0.0f, 320.0f), Vector2(80.0f, 80.f), 10, Vector2::Zero, 0.1);
		at->CreateReverse(L"Caniboar_Turn_Reverse", atlas, atlasAlpha, Vector2(0.0f, 320.0f), Vector2(80.0f, 80.f), 10, Vector2::Zero, 0.1);

		atlas = Resources::Find<Mn::graphics::Texture>(L"Hungry_Guppy_Turn_Sprite");
		atlasAlpha = Resources::Find<Mn::graphics::Texture>(L"Hungry_Guppy_Turn_Sprite_Alpha");

		at->Create(L"Caniboar_Hungry_Turn", atlas, atlasAlpha, Vector2(0.0f, 320.0f), Vector2(80.0f, 80.f), 10, Vector2::Zero, 0.1);
		at->CreateReverse(L"Caniboar_Hungry_Turn_Reverse", atlas, atlasAlpha, Vector2(0.0f, 320.0f), Vector2(80.0f, 80.f), 10, Vector2::Zero, 0.1);

		atlas = Resources::Find<Mn::graphics::Texture>(L"Guppy_Eat_Sprite");
		atlasAlpha = Resources::Find<Mn::graphics::Texture>(L"Guppy_Eat_Sprite_Alpha");

		at->Create(L"Caniboar_Eat", atlas, atlasAlpha, Vector2(0.0f, 320.0f), Vector2(80.0f, 80.f), 10, Vector2::Zero, 0.1);

		
		atlas = Resources::Find<Mn::graphics::Texture>(L"Hungry_Guppy_Eat_Sprite");
		atlasAlpha = Resources::Find<Mn::graphics::Texture>(L"Hungry_Guppy_Eat_Sprite_Alpha");

		at->Create(L"Caniboar_Hungry_Eat", atlas, atlasAlpha, Vector2(0.0f, 320.0f), Vector2(80.0f, 80.f), 10, Vector2::Zero, 0.1);

		atlas = Resources::Find<Mn::graphics::Texture>(L"Hungry_Guppy_Death_Sprite");
		atlasAlpha = Resources::Find<Mn::graphics::Texture>(L"Hungry_Guppy_Death_Sprite_Alpha");

		at->Create(L"Caniboar_Death", atlas, atlasAlpha, Vector2(0.0f, 320.0f), Vector2(80.0f, 80.f), 10, Vector2::Zero, 0.1);
		at->CreateReverse(L"Caniboar_Death_Reverse", atlas, atlasAlpha, Vector2(0.0f, 320.0f), Vector2(80.0f, 80.f), 10, Vector2::Zero, 0.1);

		at->PlayAnimation(L"Caniboar_Swim", true);

		at->CompleteEvent(L"Caniboar_Turn") = std::bind(&CaniboarRender::AfterSwim, this);
		at->CompleteEvent(L"Caniboar_Turn_Reverse") = std::bind(&CaniboarRender::AfterSwim, this);
		at->CompleteEvent(L"Caniboar_Hungry_Turn") = std::bind(&CaniboarRender::AfterSwim, this);
		at->CompleteEvent(L"Caniboar_Hungry_Turn_Reverse") = std::bind(&CaniboarRender::AfterSwim, this);
	}
	void CaniboarRender::Update()
	{
	}
	void CaniboarRender::LateUpdate()
	{
	}
	void CaniboarRender::Render()
	{
	}
	void CaniboarRender::AfterSwim()
	{
		Animator* at = GetOwner()->GetComponent<Animator>();
		at->PlayAnimation(L"Caniboar_Swim", true);
	}
}
#include "MnUltravoreRender.h"

#include "MnMeshRenderer.h"
#include "MnAnimator.h"
#include "MnGameObject.h"
#include "MnResources.h"
#include "MnCollider2D.h"

namespace Mn
{
	UltravoreRender::UltravoreRender()
	{
	}
	UltravoreRender::~UltravoreRender()
	{
	}
	void UltravoreRender::Initialize()
	{

		Collider2D* col = GetOwner()->AddComponent<Collider2D>();
		col->SetSize(Vector2(0.45f, 0.45f));

		MeshRenderer* mr = GetOwner()->AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"SpriteAnimaionMaterial"));
		Animator* at = GetOwner()->AddComponent<Animator>();

		std::shared_ptr<Mn::graphics::Texture> atlas = Resources::Load<Mn::graphics::Texture>(L"Ultravore_Sprite",L"..\\Resources\\Texture\\Fish\\Ultravore\\ultravore.jpg");
		std::shared_ptr<Mn::graphics::Texture> atlasAlpha = Resources::Load<Mn::graphics::Texture>(L"Ultravore_Sprite_Alpha", L"..\\Resources\\Texture\\Fish\\Ultravore\\_ultravore.jpg");

		at->Create(L"Ultravore_Swim", atlas, atlasAlpha, Vector2::Zero, Vector2(160.0f, 160.0f),10, Vector2::Zero, 0.1f);
		at->Create(L"Ultravore_Eat", atlas, atlasAlpha, Vector2(0.0f,160.0f), Vector2(160.0f, 160.0f),10, Vector2::Zero, 0.1f);
		at->Create(L"Ultravore_Turn_Right", atlas, atlasAlpha, Vector2(0.0f,320.0f), Vector2(160.0f, 160.0f),10, Vector2::Zero, 0.1f);
		at->CreateReverse(L"Ultravore_Turn_Left", atlas, atlasAlpha, Vector2(0.0f,320.0f), Vector2(160.0f, 160.0f),10, Vector2::Zero, 0.1f);
		at->Create(L"Ultravore_Death", atlas, atlasAlpha, Vector2(0.0f,480.0f), Vector2(160.0f, 160.0f),10, Vector2::Zero, 0.1f);
		at->CreateReverse(L"Ultravore_Death_Reverse", atlas, atlasAlpha, Vector2(0.0f,480.0f), Vector2(160.0f, 160.0f),10, Vector2::Zero, 0.1f);

		at->CompleteEvent(L"Ultravore_Death") = std::bind(&UltravoreRender::afterDeath, this);
		at->CompleteEvent(L"Ultravore_Death_Reverse") = std::bind(&UltravoreRender::afterDeath, this);
		at->CompleteEvent(L"Ultravore_Eat") = std::bind(&UltravoreRender::afterEat, this);

		at->PlayAnimation(L"Ultravore_Swim", true);
	}
	void UltravoreRender::Update()
	{
	}
	void UltravoreRender::LateUpdate()
	{
	}
	void UltravoreRender::Render()
	{
	}
	void UltravoreRender::afterDeath()
	{
		GetOwner()->State(GameObject::eState::Dead);
	}
	void UltravoreRender::afterEat()
	{
		Animator* at = GetOwner()->GetComponent<Animator>();
		at->PlayAnimation(L"Ultravore_Swim", true);
	}
}
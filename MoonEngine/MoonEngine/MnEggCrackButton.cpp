#include "MnEggCrackButton.h"
#include "MnResources.h"
#include "MnAnimator.h"
#include "MnCollider2D.h"
namespace Mn
{
	EggCrackButton::EggCrackButton()
	{
	}
	EggCrackButton::~EggCrackButton()
	{
	}
	void EggCrackButton::Initialize()
	{
		Collider2D* coll = AddComponent<Collider2D>();

		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"SpriteAnimaionMaterial"));
		mr->FlipX(0);

		Animator* at = AddComponent<Animator>();

		std::shared_ptr<Mn::graphics::Texture> atlas
			= Resources::Load<Mn::graphics::Texture>(L"CrackButton_Sprite", L"..\\Resources\\Texture\\UI\\button\\fatbutton.jpg");
		std::shared_ptr<Mn::graphics::Texture> atlasAlpha
			= Resources::Load<Mn::graphics::Texture>(L"CrackButton_Sprite_Alpha", L"..\\Resources\\Texture\\UI\\button\\fatbutton_.jpg");

		at->Create(L"OkayButtonOff", atlas, atlasAlpha, Vector2::Zero, Vector2(209.0f, 41.0f), 1, Vector2::Zero, 0.1f);
		at->Create(L"OkayButtonOn", atlas, atlasAlpha, Vector2(209.0f, 0.0f), Vector2(209.0f, 41.0f), 1, Vector2::Zero, 0.1f);
		at->Create(L"OkayButtonClick", atlas, atlasAlpha, Vector2(418.0f, 0.0f), Vector2(209.0f, 41.0f), 1, Vector2::Zero, 0.1f);

		at->PlayAnimation(L"OkayButtonOff", true);
	}
	void EggCrackButton::Update()
	{
		GameObject::Update();
	}
	void EggCrackButton::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void EggCrackButton::Render()
	{
		GameObject::Render();
	}
	void EggCrackButton::OnClick()
	{
		Animator* at = GetComponent<Animator>();
		at->PlayAnimation(L"OkayButtonClick", true);
	}
	void EggCrackButton::OnClick(Vector3 pos)
	{
	}
	void EggCrackButton::MouseOn()
	{
		Animator* at = GetComponent<Animator>();
		if (at->AnimationComplete())
			at->PlayAnimation(L"OkayButtonOn",true);
	}
	void EggCrackButton::MouseOff()
	{
		Animator* at = GetComponent<Animator>();
		if (at->AnimationComplete())
			at->PlayAnimation(L"OkayButtonOff", true);
	}
}
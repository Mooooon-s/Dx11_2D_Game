#include "MnEggCrackButton.h"
#include "MnResources.h"
#include "MnAnimator.h"
#include "MnCollider2D.h"

#include "MnObject.h"
#include "MnStinky.h"
#include "MnNiko.h"
#include "MnZorf.h"
#include "MnPrego.h"
#include "MnAmp.h"

#define NIKO_POSITION Vector3(-1.4f, -0.4f, 100.0f)
#define STINKY_POSITION Vector3(0.0f, -1.2f, 100.1f)
#define ZORF_POSITION Vector3(0.0f, 0.0f, 4.0f)
#define PREGO_POSITION Vector3(0.0f, 0.0f, 6.0f)
#define AMP_POSITION Vector3(0.0f, 1.0f, 7.0f)




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
		Transform* tr = GetComponent<Transform>();
		tr->Scale(Vector3(2.0f, 0.25f,0.0f));

		Collider2D* coll = AddComponent<Collider2D>();

		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"SpriteAnimaionMaterial"));
		mr->FlipX(0);

		Animator* at = AddComponent<Animator>();

		std::shared_ptr<Mn::graphics::Texture> atlas
			= Resources::Load<Mn::graphics::Texture>(L"CrackButton_Sprite", L"..\\Resources\\Texture\\UI\\button\\fatbuttonOff.jpg");
		std::shared_ptr<Mn::graphics::Texture> atlasAlpha
			= Resources::Load<Mn::graphics::Texture>(L"CrackButton_Sprite_Alpha", L"..\\Resources\\Texture\\UI\\button\\fatbuttonAlpha_.jpg");
		at->Create(L"OkayButtonOff", atlas, atlasAlpha, Vector2::Zero, Vector2(209.0f, 41.0f), 1, Vector2::Zero, 0.1f);

		atlas = Resources::Load<Mn::graphics::Texture>(L"CrackButton_ON_Sprite", L"..\\Resources\\Texture\\UI\\button\\fatbuttonOn.jpg");
		at->Create(L"OkayButtonOn", atlas, atlasAlpha, Vector2::Zero, Vector2(209.0f, 41.0f), 1, Vector2::Zero, 0.1f);

		atlas = Resources::Load<Mn::graphics::Texture>(L"CrackButton_CLICK_Sprite", L"..\\Resources\\Texture\\UI\\button\\fatbuttonClick.jpg");
		at->Create(L"OkayButtonClick", atlas, atlasAlpha, Vector2::Zero, Vector2(209.0f, 41.0f), 1, Vector2::Zero, 0.1f);

		at->CompleteEvent(L"OkayButtonClick") = std::bind(&EggCrackButton::ClickEvent, this);

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

	}
	void EggCrackButton::OnClick(Vector3 pos)
	{
		Animator* at = GetComponent<Animator>();
		at->PlayAnimation(L"OkayButtonClick", true);
		SpawnPet();
		_ECE->OnClick();
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
	void EggCrackButton::ClickEvent()
	{
		
	}
	void EggCrackButton::SpawnPet()
	{
		GameObject* pet = nullptr;
		switch (_Icon)
		{
		case eIcon::Niko:
			pet = object::Instantiate<Niko>(NIKO_POSITION, eLayerType::Pet);
			break;
		case eIcon::Stinky:
			pet = object::Instantiate<Stinky>(STINKY_POSITION, eLayerType::Pet);
			break;
		case eIcon::Zorf:
			pet = object::Instantiate<Zorf>(ZORF_POSITION, eLayerType::Pet);
			break;
		case eIcon::Prego:
			pet = object::Instantiate<Prego>(PREGO_POSITION, eLayerType::Pet);
			break;
		case eIcon::Amp:
			pet = object::Instantiate<Amp>(AMP_POSITION, eLayerType::Pet);
			break;
		case eIcon::End:
			break;
		default:
			break;
		}
		pet->Initialize();
	}
}
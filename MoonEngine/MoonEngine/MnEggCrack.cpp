#include "MnEggCrack.h"
#include "MnResources.h"
#include "MnAnimator.h"
#include "MnCreateIcon.h"

#include "MnNikoIcon.h"
#include "MnStinkyIcon.h"
#include "MnZorfIcon.h"
#include "MnPregoIcon.h"
#include "MnAmpIcon.h"

#define ICON_POSITION Vector3(0.0f, 0.85f, -9.1f)

Mn::EggCrack::EggCrack()
{
}

Mn::EggCrack::~EggCrack()
{
}

void Mn::EggCrack::Initialize()
{
	Transform* tr = GetComponent<Transform>();

	MeshRenderer* mr = AddComponent<MeshRenderer>();
	mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
	mr->SetMaterial(Resources::Find<Material>(L"SpriteAnimaionMaterial"));
	mr->FlipX(0);

	Animator* at = AddComponent<Animator>();

	std::shared_ptr<Mn::graphics::Texture> atlas
		= Resources::Load<Mn::graphics::Texture>(L"EggCrack1_Sprite", L"..\\Resources\\Texture\\Item\\Egg\\EggCrack1.jpg");
	std::shared_ptr<Mn::graphics::Texture> atlasAlpha
		= Resources::Load<Mn::graphics::Texture>(L"EggCrack1_Sprite_Alpha", L"..\\Resources\\Texture\\Item\\Egg\\_EggCrack1.jpg");
	at->Create(L"EggCrack1", atlas, atlasAlpha, Vector2::Zero, Vector2(118.0f, 145.0f), 13, Vector2::Zero, 0.1f);

	atlas = Resources::Load<Mn::graphics::Texture>(L"EggCrack2_Sprite", L"..\\Resources\\Texture\\Item\\Egg\\EggCrack2.jpg");
	atlasAlpha = Resources::Load<Mn::graphics::Texture>(L"EggCrack2_Sprite_Alpha", L"..\\Resources\\Texture\\Item\\Egg\\_EggCrack2.jpg");
	at->Create(L"EggCrack2", atlas, atlasAlpha, Vector2::Zero, Vector2(118.0f, 145.0f), 10, Vector2::Zero, 0.1f);


	at->CompleteEvent(L"EggCrack1") = std::bind(&EggCrack::Afterstep1, this);
	at->CompleteEvent(L"EggCrack2") = std::bind(&EggCrack::Afterstep2, this);
	
	at->PlayAnimation(L"EggCrack1", true);
}

void Mn::EggCrack::Update()
{

	GameObject::Update();
}

void Mn::EggCrack::LateUpdate()
{
	GameObject::LateUpdate();
}

void Mn::EggCrack::Render()
{
	GameObject::Render();
}

void Mn::EggCrack::Afterstep1()
{
	Animator* at = GetComponent<Animator>();
	at->PlayAnimation(L"EggCrack2", true);
}

void Mn::EggCrack::Afterstep2()
{
	CreateIconSet();
	this->State(GameObject::eState::Dead);
}

void Mn::EggCrack::CreateIconSet()
{
	GameObject* icon=nullptr;
	switch (_Icon)
	{
	case Mn::enums::eIcon::Niko:
		icon = CreateIcon<NikoIcon>(ICON_POSITION);
		break;
	case Mn::enums::eIcon::Stinky:
		icon = CreateIcon<StinkyIcon>(ICON_POSITION);
		break;
	case Mn::enums::eIcon::Zorf:
		icon = CreateIcon<ZorfIcon>(ICON_POSITION);
		break;
	case Mn::enums::eIcon::Prego:
		icon = CreateIcon<PregoIcon>(ICON_POSITION);
		break;
	case Mn::enums::eIcon::Amp:
		icon = CreateIcon<AmpIcon>(ICON_POSITION);
		break;
	case Mn::enums::eIcon::End:
		break;
	default:
		break;
	}
	icon->Initialize();
	_EggCrackEvent->AddObj(icon);
}

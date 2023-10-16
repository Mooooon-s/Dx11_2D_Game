#include "MnAmpRender.h"
#include "MnGameObject.h"
#include "MnResources.h"
#include "MnAnimator.h"
#include "MnCollider2D.h"


namespace Mn
{
	AmpRender::AmpRender()
	{
	}
	AmpRender::~AmpRender()
	{
	}
	void AmpRender::Initialize()
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();
		tr->Scale(Vector3(1.0f, 0.5f, 0.0f));

		Collider2D* coll = GetOwner()->AddComponent<Collider2D>();
		coll->SetSize(Vector2(1.0f, 0.5f));

		MeshRenderer* mr = GetOwner()->AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"SpriteAnimaionMaterial"));

		Animator* at = GetOwner()->AddComponent<Animator>();
		std::shared_ptr<Mn::graphics::Texture> atlas
			= Resources::Load<Mn::graphics::Texture>(L"Amp_Atlas", L"..\\Resources\\Texture\\Pet\\amp\\amp.jpg");
		std::shared_ptr<Mn::graphics::Texture> atlasAlpha
			= Resources::Load<Mn::graphics::Texture>(L"Amp_Atlas_alpha", L"..\\Resources\\Texture\\Pet\\amp\\_amp.jpg");

		at->Create(L"Amp_Swim", atlas, atlasAlpha, Vector2::Zero, Vector2(160,60), 10, Vector2::Zero, 0.1f);
		at->Create(L"Amp_Turn", atlas, atlasAlpha, Vector2(0.0f,60.0f), Vector2(160,60), 10, Vector2::Zero, 0.1f);
		at->CreateReverse(L"Amp_Turn_Reverse", atlas, atlasAlpha, Vector2(0.0f,60.0f), Vector2(160,60), 10, Vector2::Zero, 0.1f);


		atlas = Resources::Load<Mn::graphics::Texture>(L"Amp_Charged_Atlas", L"..\\Resources\\Texture\\Pet\\amp\\ampCharged.jpg");
		at->Create(L"Amp_Charged_Swim", atlas, atlasAlpha, Vector2::Zero, Vector2(160, 60), 10, Vector2::Zero, 0.1f);
		at->Create(L"Amp_Charged_Turn", atlas, atlasAlpha, Vector2(0.0f, 60.0f), Vector2(160, 60), 10, Vector2::Zero, 0.1f);
		at->CreateReverse(L"Amp_Charged_Turn_Reverse", atlas, atlasAlpha, Vector2(0.0f, 60.0f), Vector2(160, 60), 10, Vector2::Zero, 0.1f);

		at->CompleteEvent(L"Amp_Turn") = std::bind(&AmpRender::AfterTurn, this);
		at->CompleteEvent(L"Amp_Turn_Reverse") = std::bind(&AmpRender::AfterTurn, this);

		at->CompleteEvent(L"Amp_Charged_Turn") = std::bind(&AmpRender::AfterChargeTurn, this);
		at->CompleteEvent(L"Amp_Charged_Turn_Reverse") = std::bind(&AmpRender::AfterChargeTurn, this);

		at->PlayAnimation(L"Amp_Swim",true);
	}
	void AmpRender::Update()
	{
	}
	void AmpRender::LateUpdate()
	{
	}
	void AmpRender::Render()
	{
	}
	void AmpRender::AfterTurn()
	{
		Animator* at = GetOwner()->AddComponent<Animator>();
		at->PlayAnimation(L"Amp_Swim", true);
	}
	void AmpRender::AfterChargeTurn()
	{
		Animator* at = GetOwner()->AddComponent<Animator>();
		at->PlayAnimation(L"Amp_Charged_Swim", true);
	}
}
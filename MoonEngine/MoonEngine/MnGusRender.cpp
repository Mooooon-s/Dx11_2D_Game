#include "MnGusRender.h"
#include "MnResources.h"
#include "MnGameObject.h"
#include "MnAnimator.h"
#include "MnCollider2D.h"

namespace Mn
{
	GusRender::GusRender()
	{

	}
	GusRender::~GusRender()
	{

	}
	void GusRender::Initialize()
	{
		Collider2D* coll = GetOwner()->AddComponent < Collider2D>();
		coll->SetSize(Vector2(0.5f, 1.0f));

		Transform* tr = GetOwner()->GetComponent<Transform>();
		tr->Scale(Vector3(1.0f, 1.0f, 0.0f));


		MeshRenderer* mr = GetOwner()->AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"SpriteAnimaionMaterial"));

		Animator* at = GetOwner()->AddComponent<Animator>();
		std::shared_ptr<Mn::graphics::Texture> atlas
			= Resources::Load<Mn::graphics::Texture>(L"Gus_Atlas", L"..\\Resources\\Texture\\Boss\\gus.jpg");
		std::shared_ptr<Mn::graphics::Texture> atlasAlpha
			= Resources::Load<Mn::graphics::Texture>(L"Gus_Atlas_alpha", L"..\\Resources\\Texture\\Boss\\_gus.jpg");

		at->Create(L"Gus_Swim", atlas, atlasAlpha, Vector2::Zero, Vector2(160,160), 10, Vector2::Zero, 0.1f);
		at->Create(L"Gus_Turn", atlas, atlasAlpha, Vector2(0.0f,160.0f), Vector2(160,160), 10, Vector2::Zero, 0.1f);
		at->CreateReverse(L"Gus_Turn_Reverse", atlas, atlasAlpha, Vector2(0.0f, 160.0f), Vector2(160,160), 10, Vector2::Zero, 0.1f);
		at->Create(L"Gus_Eat", atlas, atlasAlpha, Vector2(0.0f,320.0f), Vector2(160,160), 10, Vector2::Zero, 0.1f);

		at->CompleteEvent(L"Gus_Turn") = std::bind(&GusRender::afterTurn, this);
		at->CompleteEvent(L"Gus_Turn_Reverse") = std::bind(&GusRender::afterTurn, this);
		at->CompleteEvent(L"Gus_Eat") = std::bind(&GusRender::afterEat, this);

		at->PlayAnimation(L"Gus_Swim", true);
	}
	void GusRender::Update()
	{
	}
	void GusRender::LateUpdate()
	{
	}
	void GusRender::Render()
	{
	}
	void GusRender::afterTurn()
	{
		Animator* at = GetOwner()->AddComponent<Animator>();
		if(at != nullptr || at->GetActiveAnimation()!=nullptr)
			at->PlayAnimation(L"Gus_Swim", true);
	}
	void GusRender::afterEat()
	{
		Animator* at = GetOwner()->AddComponent<Animator>();
		if(at != nullptr || at->GetActiveAnimation() != nullptr)
			at->PlayAnimation(L"Gus_Swim", true);
	}
}
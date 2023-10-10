#include "MnItchyRender.h"

#include "MnMeshRenderer.h"
#include "MnResources.h"
#include "MnAnimator.h"
#include "MnGameObject.h"

namespace Mn
{
	ItchyRender::ItchyRender()
	{
	}
	ItchyRender::~ItchyRender()
	{
	}
	void ItchyRender::Initialize()
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();
		tr->Scale(Vector3(0.5f, 0.5f, 0.0f));


		MeshRenderer* mr = GetOwner()->AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"SpriteAnimaionMaterial"));

		Animator* at = GetOwner()->AddComponent<Animator>();
		std::shared_ptr<Mn::graphics::Texture> atlas
			= Resources::Load<Mn::graphics::Texture>(L"Itchy_Atlas", L"..\\Resources\\Texture\\Pet\\itchy\\itchy.jpg");
		std::shared_ptr<Mn::graphics::Texture> atlasAlpha
			= Resources::Load<Mn::graphics::Texture>(L"Itchy_Atlas_alpha", L"..\\Resources\\Texture\\Pet\\itchy\\_itchy.jpg");

		at->Create(L"Itchy_Idle_Swim", atlas, atlasAlpha, Vector2::Zero, Vector2(80.0f, 80.0f), 10, Vector2::Zero, 0.1f);
		at->Create(L"Itchy_Idle_Turn_Right", atlas, atlasAlpha, Vector2(0.0f,80.0f), Vector2(80.0f, 80.0f), 10, Vector2::Zero, 0.1f);
		at->CreateReverse(L"Itchy_Idle_Turn_Left", atlas, atlasAlpha, Vector2(0.0f,80.0f), Vector2(80.0f, 80.0f), 10, Vector2::Zero, 0.1f);
		at->Create(L"Itchy_Attack_Swim", atlas, atlasAlpha, Vector2(0.0f,160.0f), Vector2(80.0f, 80.0f), 10, Vector2::Zero, 0.1f);
		at->Create(L"Itchy_Attack_Turn_Right", atlas, atlasAlpha, Vector2(0.0f,240.0f), Vector2(80.0f, 80.0f), 10, Vector2::Zero, 0.1f);
		at->CreateReverse(L"Itchy_Attack_Turn_Left", atlas, atlasAlpha, Vector2(0.0f,240.0f), Vector2(80.0f, 80.0f), 10, Vector2::Zero, 0.1f);


		at->CompleteEvent(L"Itchy_Idle_Turn_Right") = std::bind(&ItchyRender::AfterIdleTurn, this);
		at->CompleteEvent(L"Itchy_Idle_Turn_Left") = std::bind(&ItchyRender::AfterIdleTurn, this);
		at->CompleteEvent(L"Itchy_Attack_Turn_Right") = std::bind(&ItchyRender::AfterAttaclTurn, this);
		at->CompleteEvent(L"Itchy_Attack_Turn_Left") = std::bind(&ItchyRender::AfterAttaclTurn, this);

		at->PlayAnimation(L"Itchy_Idle_Swim", true);
	}
	void ItchyRender::Update()
	{
	}
	void ItchyRender::LateUpdate()
	{
	}
	void ItchyRender::Render()
	{
	}
	void ItchyRender::AfterIdleTurn()
	{
		Animator* at = GetOwner()->GetComponent<Animator>();
		at->PlayAnimation(L"Itchy_Idle_Swim", true);
	}
	void ItchyRender::AfterAttaclTurn()
	{
		Animator* at = GetOwner()->GetComponent<Animator>();
		at->PlayAnimation(L"Itchy_Attack_Swim", true);
	}
}
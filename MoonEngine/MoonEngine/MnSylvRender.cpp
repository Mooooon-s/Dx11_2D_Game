#include "MnSylvRender.h"

#include "MnMeshRenderer.h"
#include "MnAnimator.h"
#include "MnCollider2D.h"
#include "MnGameObject.h"
#include "MnResources.h"

namespace Mn
{
	SylvRender::SylvRender()
	{
	}
	SylvRender::~SylvRender()
	{
	}
	void SylvRender::Initialize()
	{
		Collider2D* coll = GetOwner()->AddComponent<Collider2D>();
		coll->SetSize(Vector2(0.5f, 0.5f));

		MeshRenderer* mr = GetOwner()->AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"BalrogSpriteAnimaionMaterial"));

		Animator* at = GetOwner()->AddComponent<Animator>();
		std::shared_ptr<Mn::graphics::Texture> atlas
			= Resources::Load<Mn::graphics::Texture>(L"Sylv_Atlas", L"..\\Resources\\Texture\\Boss\\sylv.jpg");
		std::shared_ptr<Mn::graphics::Texture> atlasAlpha
			= Resources::Load<Mn::graphics::Texture>(L"Sylv_Atlas_Alpha", L"..\\Resources\\Texture\\Boss\\_sylv.jpg");

		at->Create(L"Sylv_Idle", atlas, atlasAlpha, Vector2::Zero, Vector2(160.0f, 160.0f), 10, Vector2::Zero, 0.1f);
		at->Create(L"Sylv_Turn_Right", atlas, atlasAlpha, Vector2(0.0f,160.0f), Vector2(160.0f, 160.0f), 10, Vector2::Zero, 0.1f);
		at->CreateReverse(L"Sylv_Turn_Left", atlas, atlasAlpha, Vector2(0.0f,160.0f), Vector2(160.0f, 160.0f), 10, Vector2::Zero, 0.1f);

		at->CompleteEvent(L"Sylv_Turn_Right") = std::bind(&SylvRender::AfterTurn, this);
		at->CompleteEvent(L"Sylv_Turn_Left") = std::bind(&SylvRender::AfterTurn, this);

		at->PlayAnimation(L"Sylv_Idle",true);
	}
	void SylvRender::Update()
	{
	}
	void SylvRender::LateUpdate()
	{
	}
	void SylvRender::Render()
	{
	}
	void SylvRender::AfterTurn()
	{
		Animator* at = GetOwner()->GetComponent<Animator>();
		at->PlayAnimation(L"Sylv_Idle",true);
	}
}
#include "MnBalrogRenderScript.h"
#include "MnResources.h"
#include "MnTexture.h"
#include "MnMeshRenderer.h"
#include "MnGameObject.h"
#include "MnAnimator.h"
#include "MnCollider2D.h"


namespace Mn
{
	BalrogRenderScript::BalrogRenderScript()
	{
	}
	BalrogRenderScript::~BalrogRenderScript()
	{
	}
	void BalrogRenderScript::Initialize()
	{
		Collider2D* coll = GetOwner()->AddComponent<Collider2D>();
		coll->SetSize(Vector2(0.5f, 0.5f));

		MeshRenderer* mr = GetOwner()->AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"BalrogSpriteAnimaionMaterial"));

		Animator* at = GetOwner()->AddComponent<Animator>();
		std::shared_ptr<Mn::graphics::Texture> atlas 
			= Resources::Load<Mn::graphics::Texture>(L"Balrog_Atlas",L"..\\Resources\\Texture\\Boss\\balrog.jpg");
		std::shared_ptr<Mn::graphics::Texture> atlasAlpha
			= Resources::Load<Mn::graphics::Texture>(L"Balrog_Atlas_Alpha", L"..\\Resources\\Texture\\Boss\\_balrog.jpg");

		at->Create(L"Balrog_Swim", atlas, atlasAlpha, Vector2(0.0f, 0.0f), Vector2(160.0f,160.0f), 10, Vector2::Zero, 0.1f);
		at->Create(L"Balrog_Turn_Right", atlas, atlasAlpha, Vector2(0.0f, 160.0f), Vector2(160.0f,160.0f), 10, Vector2::Zero, 0.1f);
		at->CreateReverse(L"Balrog_Turn_Left", atlas, atlasAlpha, Vector2(0.0f, 160.0f), Vector2(160.0f,160.0f), 10, Vector2::Zero, 0.1f);

		at->CompleteEvent(L"Balrog_Turn_Right") = std::bind(&BalrogRenderScript::AfterTurn, this);
		at->CompleteEvent(L"Balrog_Turn_Left") = std::bind(&BalrogRenderScript::AfterTurn, this);

		at->PlayAnimation(L"Balrog_Swim", true);
	}
	void BalrogRenderScript::Update()
	{
	}
	void BalrogRenderScript::LateUpdate()
	{
	}
	void BalrogRenderScript::Render()
	{
	}
	void BalrogRenderScript::AfterTurn()
	{
		Animator* at = GetOwner()->GetComponent<Animator>();
		at->PlayAnimation(L"Balrog_Swim", true);
	}
}
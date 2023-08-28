#include "MnStinkyRenderScript.h"
#include "MnMeshRenderer.h"
#include "MnTexture.h"
#include "MnAnimator.h"
#include "MnResources.h"
#include "MnGameObject.h"
#include "MnCollider2D.h"

namespace Mn
{
	StinkyRenderScript::StinkyRenderScript()
	{
	}
	StinkyRenderScript::~StinkyRenderScript()
	{
	}
	void StinkyRenderScript::Initialize()
	{
		Collider2D* coll = GetOwner()->AddComponent<Collider2D>();
		coll->SetSize(Vector2(0.5f, 0.5f));

		MeshRenderer* mr = GetOwner()->AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"StinkySpriteAnimaionMaterial"));

		Animator* at = GetOwner()->AddComponent<Animator>();
		std::shared_ptr<Mn::graphics::Texture> atlas = Resources::Load<Mn::graphics::Texture>(L"Stinky", L"..\\Resources\\Texture\\Pet\\stinky\\stinky.jpg");
		std::shared_ptr<Mn::graphics::Texture> atlasAlpha = Resources::Load<Mn::graphics::Texture>(L"Stinky_Alpha", L"..\\Resources\\Texture\\Pet\\stinky\\_stinky.jpg");

		at->Create(L"Stinky_Move", atlas, atlasAlpha, Vector2::Zero, Vector2(80.0f, 80.0f), 10,Vector2::Zero, 0.1f);
		at->Create(L"Stinky_Turn", atlas, atlasAlpha, Vector2(0.0f,80.0f), Vector2(80.0f, 80.0f), 10,Vector2::Zero, 0.1f);
		at->CreateReverse(L"Stinky_Turn_Reverse", atlas, atlasAlpha, Vector2(0.0f,80.0f), Vector2(80.0f, 80.0f), 10,Vector2::Zero, 0.1f);
		at->Create(L"Stinky_Hide", atlas, atlasAlpha, Vector2(0.0f,160.0f), Vector2(80.0f, 80.0f), 10,Vector2::Zero, 0.1f);
		at->CreateReverse(L"Stinky_Hide_Reverse", atlas, atlasAlpha, Vector2(0.0f,160.0f), Vector2(80.0f, 80.0f), 10,Vector2::Zero, 0.1f);
		
		at->CompleteEvent(L"Stinky_Turn") = std::bind(&StinkyRenderScript::AfterTurn, this);
		at->CompleteEvent(L"Stinky_Turn_Reverse") = std::bind(&StinkyRenderScript::AfterTurn, this);
		at->StartEvent(L"Stinky_Turn") = std::bind(&StinkyRenderScript::Direction2Right,this);
		at->StartEvent(L"Stinky_Turn_Reverse") = std::bind(&StinkyRenderScript::Direction2Left,this);


		at->PlayAnimation(L"Stinky_Move", true);
	}
	void StinkyRenderScript::Update()
	{
	}
	void StinkyRenderScript::LateUpdate()
	{
	}
	void StinkyRenderScript::Render()
	{
	}
	void StinkyRenderScript::Direction2Right()
	{
		MeshRenderer* mr = GetOwner()->GetComponent<MeshRenderer>();
		mr->FlipX(1);
	}
	void StinkyRenderScript::Direction2Left()
	{
		MeshRenderer* mr = GetOwner()->GetComponent<MeshRenderer>();
		mr->FlipX(0);
	}
	void StinkyRenderScript::AfterTurn()
	{
		Animator* at = GetOwner()->GetComponent<Animator>();
		at->PlayAnimation(L"Stinky_Move",true);
	}
}
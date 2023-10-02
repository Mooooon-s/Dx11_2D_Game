#include "MnZorfRender.h"
#include "MnResources.h"
#include "MnMeshRenderer.h"
#include "MnAnimator.h"
#include "MnGameObject.h"

namespace Mn
{
	ZorfRender::ZorfRender()
	{
	}
	ZorfRender::~ZorfRender()
	{
	}
	void ZorfRender::Initialize()
	{
		MeshRenderer* mr = GetOwner()->AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"ZorfSpriteAnimaionMaterial"));

		Animator* at = GetOwner()->AddComponent<Animator>();
		std::shared_ptr<Mn::graphics::Texture> atlas
			= Resources::Load<Mn::graphics::Texture>(L"Zorf_Idle", L"..\\Resources\\Texture\\Pet\\zorf\\zorf.jpg");
		std::shared_ptr<Mn::graphics::Texture> atlasAlpha
			= Resources::Load<Mn::graphics::Texture>(L"Zorf_Idle_alpha", L"..\\Resources\\Texture\\Pet\\zorf\\_zorf.jpg");

		at->Create(L"Zorf_Swim",atlas, atlasAlpha,Vector2::Zero,Vector2( 80.0f,80.0f),10,Vector2::Zero,0.1f);
		at->Create(L"Zorf_Turn",atlas, atlasAlpha,Vector2(0.0f,80.0f),Vector2( 80.0f,80.0f),10,Vector2::Zero,0.1f);
		at->CreateReverse(L"Zorf_turn_Reverse",atlas, atlasAlpha,Vector2(0.0f, 80.0f),Vector2( 80.0f,80.0f),10,Vector2::Zero,0.1f);
		at->Create(L"Zorf_Feed",atlas, atlasAlpha,Vector2(0.0f, 160.0f),Vector2( 80.0f,80.0f),10,Vector2::Zero,0.1f);

		at->PlayAnimation(L"Zorf_Swim", true);
	}
	void ZorfRender::Update()
	{
	}
	void ZorfRender::LateUpdate()
	{
	}
	void ZorfRender::Render()
	{
	}
}
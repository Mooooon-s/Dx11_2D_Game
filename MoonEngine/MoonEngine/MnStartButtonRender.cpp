#include "MnAnimator.h"
#include "MnGameObject.h"
#include "MnMeshRenderer.h"
#include "MnResources.h"
#include "MnStartButtonRender.h"

namespace Mn
{
	StartButtonRender::StartButtonRender()
	{
	}
	StartButtonRender::~StartButtonRender()
	{
	}
	void StartButtonRender::Initialize()
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();
		tr->Scale(1.6f, 0.3f,1.f);
		tr->Position(-0.1f, -1.45, 1.f);

		MeshRenderer* mr = GetOwner()->AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"SpriteAnimaionMaterial"));
		Animator* at = GetOwner()->AddComponent<Animator>();

		std::shared_ptr<Mn::graphics::Texture> atlas 
			= Resources::Load<Mn::graphics::Texture>(L"StartButton_Sprite",L"..\\Resources\\Texture\\UI\\bar\\loaderplay.jpg");
		std::shared_ptr<Mn::graphics::Texture> atlasAlpha 
			= Resources::Load<Mn::graphics::Texture>(L"StartButton_Sprite_Alpha", L"..\\Resources\\Texture\\UI\\bar\\loaderplay_.jpg");

		at->Create(L"StartButton", atlas, atlasAlpha, Vector2::Zero, Vector2(250.f, 31.0f), 1, Vector2::Zero, 0.1f);

		at->PlayAnimation(L"StartButton", true);
	}
	void StartButtonRender::Update()
	{
	}
	void StartButtonRender::LateUpdate()
	{
	}
	void StartButtonRender::Render()
	{
	}
}
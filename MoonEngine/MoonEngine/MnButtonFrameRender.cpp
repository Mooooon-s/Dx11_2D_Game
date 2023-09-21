#include "MnButtonFrameRender.h"

#include "MnTexture.h"
#include "MnResources.h"
#include "MnAnimator.h"
#include "MnMeshRenderer.h"
#include "MnMaterial.h"
#include "MnGameObject.h"
namespace Mn
{
	ButtonFrameRender::ButtonFrameRender()
	{
	}
	ButtonFrameRender::~ButtonFrameRender()
	{
	}
	void ButtonFrameRender::Initialize()
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();
		tr->Scale(Vector3(0.35f, 0.35f, 0.0f));
		MeshRenderer* mr = GetOwner()->AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"SpriteAnimaionMaterial"));
		mr->FlipX(0);

		std::shared_ptr<Mn::graphics::Texture> atlas
			= Resources::Load<Mn::graphics::Texture>(L"Hatch", L"..\\Resources\\Texture\\UI\\bar\\HatchANIMATION.jpg");
		std::shared_ptr<Mn::graphics::Texture> atlasAlpha
			= Resources::Load<Mn::graphics::Texture>(L"Hatch_Alpha", L"..\\Resources\\Texture\\UI\\bar\\_HatchANIMATION.jpg");

		Animator* at = GetOwner()->AddComponent<Animator>();
		at->Create(L"OpenHatch", atlas, atlasAlpha, Vector2::Zero, Vector2(57, 60), 3, Vector2::Zero, 0.1f);
		at->CreateReverse(L"CloseHatch", atlas, atlasAlpha, Vector2::Zero, Vector2(57, 60), 3, Vector2::Zero, 0.1f);
		at->PlayAnimation(L"OpenHatch", true);

		atlas = Resources::Load<Mn::graphics::Texture>(L"Reflect", L"..\\Resources\\Texture\\UI\\bar\\_MBREFLECTION.jpg");
		atlasAlpha = Resources::Load<Mn::graphics::Texture>(L"Reflect_Alpha", L"..\\Resources\\Texture\\UI\\bar\\_MBREFLECTION.jpg");
		at->Create(L"Reflect", atlas, atlasAlpha, Vector2::Zero, Vector2(58, 60), 1, Vector2::Zero, 0.1f);

		at->CompleteEvent(L"OpenHatch") = std::bind(&ButtonFrameRender::Reflect, this);

	}
	void ButtonFrameRender::Update()
	{
		Script::Update();
	}
	void ButtonFrameRender::LateUpdate()
	{
	}
	void ButtonFrameRender::Render()
	{
		Script::Render();
	}
	void ButtonFrameRender::Reflect()
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();
		tr->Scale(Vector3(0.45f, 0.45f, 0.0f));
		Animator* at = GetOwner()->GetComponent<Animator>();
		at->PlayAnimation(L"Reflect",true);
	}
}
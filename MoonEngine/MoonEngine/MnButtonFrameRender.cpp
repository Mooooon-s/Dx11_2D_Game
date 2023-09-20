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
		MeshRenderer* mr = GetOwner()->AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"SpriteAnimaionMaterial"));
		mr->FlipX(1);

		std::shared_ptr<Mn::graphics::Texture> atlas
			= Resources::Load<Mn::graphics::Texture>(L"Hatch", L"..\\Resources\\Texture\\UI\\bar\\HatchANIMATION.jpg");
		std::shared_ptr<Mn::graphics::Texture> atlasAlpha
			= Resources::Load<Mn::graphics::Texture>(L"Hatch_Alpha", L"..\\Resources\\Texture\\UI\\bar\\_HatchANIMATION.jpg");

		Animator* at = GetOwner()->AddComponent<Animator>();
		at->Create(L"OpenHatch", atlas, atlasAlpha, Vector2::Zero, Vector2(171, 60), 3, Vector2::Zero, 0.1f);
		at->CreateReverse(L"CloseHatch", atlas, atlasAlpha, Vector2::Zero, Vector2(171, 60), 3, Vector2::Zero, 0.1f);
		at->PlayAnimation(L"OpenHatch", false);
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
}
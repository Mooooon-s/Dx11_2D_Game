#include "MnWarpRenderScript.h"

#include "MnTexture.h"
#include "MnResources.h"
#include "MnAnimator.h"
#include "MnMeshRenderer.h"
#include "MnMaterial.h"
#include "MnGameObject.h"

namespace Mn
{
	WarpRenderScript::WarpRenderScript()
	{
	}
	WarpRenderScript::~WarpRenderScript()
	{
	}
	void WarpRenderScript::Initialize()
	{
		MeshRenderer* mr = GetOwner()->AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"SpriteAnimaionMaterial"));
		mr->FlipX(1);

		std::shared_ptr<Mn::graphics::Texture> atlas
			= Resources::Load<Mn::graphics::Texture>(L"Warp", L"..\\Resources\\Texture\\FX\\warphole\\warpglow.jpg");
		std::shared_ptr<Mn::graphics::Texture> atlasAlpha
			= Resources::Load<Mn::graphics::Texture>(L"Warp_Alpha", L"..\\Resources\\Texture\\FX\\warphole\\_warpglow.jpg");

		Animator* at = GetOwner()->AddComponent<Animator>();
		at->Create(L"Warpglow", atlas, atlasAlpha, Vector2::Zero, Vector2(100, 220), 17, Vector2::Zero, 0.1f);
		at->PlayAnimation(L"Warpglow", true);
	}
	void WarpRenderScript::Update()
	{
		Animator* at = GetOwner()->GetComponent<Animator>();
		if (at->AnimationComplete())
			GetOwner()->State(GameObject::eState::Dead);

		Script::Update();
	}
	void WarpRenderScript::LateUpdate()
	{
	}
	void WarpRenderScript::Render()
	{
	}
}
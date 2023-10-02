#include "MnDiamondRender.h"
#include "MnResources.h"
#include "MnMeshRenderer.h"
#include "MnAnimator.h"
#include "MnGameObject.h"

namespace Mn
{
	DiamondRender::DiamondRender()
	{
	}
	DiamondRender::~DiamondRender()
	{
	}
	void DiamondRender::Initialize()
	{
		MeshRenderer* mr = GetOwner()->AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"DiamondSpriteAnimaionMaterial"));

		Animator* at = GetOwner()->AddComponent<Animator>();
		std::shared_ptr<Mn::graphics::Texture> atlas = Resources::Load<Mn::graphics::Texture>(L"Coin_Idle", L"..\\Resources\\Texture\\Item\\money\\money.jpg");
		std::shared_ptr<Mn::graphics::Texture> atlasAlpha = Resources::Load<Mn::graphics::Texture>(L"Coin_Idle_alpha", L"..\\Resources\\Texture\\Item\\money\\money_.jpg");
		at->Create(L"Diamond", atlas, atlasAlpha, Vector2(0.0f, 216.0f), Vector2(72.0f, 72.0f), 10, Vector2::Zero, 0.1f);

		at->PlayAnimation(L"Diamond",true);
	}
	void DiamondRender::Update()
	{
	}
	void DiamondRender::LateUpdate()
	{
	}
	void DiamondRender::Render()
	{

	}
}
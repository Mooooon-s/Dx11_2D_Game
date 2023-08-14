#include "MnCoinRender.h"
#include "MnAnimator.h"
#include "MnGameObject.h"
#include "MnCollider2D.h"
#include "MnResources.h"
#include "MnTexture.h"
#include "MnMeshRenderer.h"
#include "MnMaterial.h"

namespace Mn
{
	CoinRender::CoinRender()
		:_Level(1)
	{
	}
	CoinRender::~CoinRender()
	{
	}
	void CoinRender::Initialize()
	{
		MeshRenderer* mr = GetOwner()->AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"CoinSpriteAnimaionMaterial"));

		Animator* at = GetOwner()->AddComponent<Animator>();
		std::shared_ptr<Mn::graphics::Texture> atlas 
			=Resources::Load<Mn::graphics::Texture>(L"Coin_Idle", L"..\\Resources\\Texture\\Item\\money\\money.jpg");
		std::shared_ptr<Mn::graphics::Texture> atlasAlpha
			= Resources::Load<Mn::graphics::Texture>(L"Coin_Idle_alpha", L"..\\Resources\\Texture\\Item\\money\\money_.jpg");
		at->Create(L"Coin_Silver", atlas, atlasAlpha, Vector2(0.0f,0.0f), Vector2(72.0f, 72.0f), 10, Vector2::Zero, 0.1f);
		at->Create(L"Coin_Gold", atlas, atlasAlpha, Vector2(0.0f,72.0f), Vector2(72.0f, 72.0f), 10, Vector2::Zero, 0.1f);

		switch (_Level)
		{
		case 2:
			at->PlayAnimation(L"Coin_Silver", true);
			break;
		case 3:
			at->PlayAnimation(L"Coin_Gold", true);
			break;
		default:
			at->PlayAnimation(L"Coin_Silver", true);
			break;
		}
	
	}
	void CoinRender::Update()
	{

	}
	void CoinRender::LateUpdate()
	{

	}
	void CoinRender::Render()
	{
	}
}
#include "MnGuppyRenderScript.h"
#include "MnGameObject.h"
#include "MnMeshRenderer.h"
#include "MnAnimator.h"
#include "MnResources.h"
#include "MnGuppy.h"

#include "MnGuppyScript.h"
#include "MnGuppyAnimationCntrl.h"

#include "MnConstantBuffer.h"
#include "MnRenderer.h"

namespace Mn
{
	GuppyRender::GuppyRender()
		:_PreState(eFishState::Full)
	{
	}
	GuppyRender::~GuppyRender()
	{
	}
	void GuppyRender::Initialize()
	{

#pragma region MeshRenderer
		MeshRenderer* mr = GetOwner()->AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"SpriteAnimaionMaterial"));
#pragma endregion
#pragma region Animator
		Animator* at = GetOwner()->AddComponent<Animator>();
#pragma region Swim
		std::shared_ptr<Mn::graphics::Texture> atlas
			= Resources::Load<Mn::graphics::Texture>(L"Guppy_Sprite", L"..\\Resources\\Texture\\Fish\\guppy\\smallswim.jpg");
		std::shared_ptr<Mn::graphics::Texture> atlasAlpha 
			= Resources::Load<Mn::graphics::Texture>(L"Guppy_Sprite_Alpha", L"..\\Resources\\Texture\\Fish\\guppy\\smallswim_.jpg");
		at->Create(L"Swim_Small", atlas, atlasAlpha, Vector2(0.0f, 0.0f), Vector2(80.0f, 80.f), 10, Vector2::Zero, 0.1);
		at->Create(L"Swim_Middle", atlas, atlasAlpha, Vector2(0.0f, 80.0f), Vector2(80.0f, 80.f), 10, Vector2::Zero, 0.1);
		at->Create(L"Swim_Large", atlas, atlasAlpha, Vector2(0.0f, 160.0f), Vector2(80.0f, 80.f), 10, Vector2::Zero, 0.1);

		atlas = Resources::Load<Mn::graphics::Texture>(L"Hungry_Guppy_Sprite", L"..\\Resources\\Texture\\Fish\\guppy\\hungryswim.jpg");
		atlasAlpha = Resources::Load<Mn::graphics::Texture>(L"Hungry_Guppy_Sprite_Alpha", L"..\\Resources\\Texture\\Fish\\guppy\\hungryswim_.jpg");
		at->Create(L"Hungry_Swim_Small", atlas, atlasAlpha, Vector2(0.0f, 0.0f), Vector2(80.0f, 80.f), 10, Vector2::Zero, 0.1);
		at->Create(L"Hungry_Swim_Middle", atlas, atlasAlpha, Vector2(0.0f, 80.0f), Vector2(80.0f, 80.f), 10, Vector2::Zero, 0.1);
		at->Create(L"Hungry_Swim_Large", atlas, atlasAlpha, Vector2(0.0f, 160.0f), Vector2(80.0f, 80.f), 10, Vector2::Zero, 0.1);
#pragma endregion
#pragma region Turn
		atlas = Resources::Load<Mn::graphics::Texture>(L"Guppy_Turn_Sprite", L"..\\Resources\\Texture\\Fish\\guppy\\smallturn.jpg");
		atlasAlpha = Resources::Load<Mn::graphics::Texture>(L"Guppy_Turn_Sprite_Alpha", L"..\\Resources\\Texture\\Fish\\guppy\\smallturn_.jpg");
		at->CreateReverse(L"Turn_Small_Revers", atlas, atlasAlpha, Vector2(0.0f, 0.0f), Vector2(80.0f, 80.f), 10, Vector2::Zero, 0.1);
		at->Create(L"Turn_Small", atlas, atlasAlpha, Vector2(0.0f, 0.0f), Vector2(80.0f, 80.f), 10, Vector2::Zero, 0.1);
		at->Create(L"Turn_Middle", atlas, atlasAlpha, Vector2(0.0f, 80.0f), Vector2(80.0f, 80.f), 10, Vector2::Zero, 0.1);
		at->Create(L"Turn_Large", atlas, atlasAlpha, Vector2(0.0f, 160.0f), Vector2(80.0f, 80.f), 10, Vector2::Zero, 0.1);

		atlas = Resources::Load<Mn::graphics::Texture>(L"Hungry_Guppy_Turn_Sprite", L"..\\Resources\\Texture\\Fish\\guppy\\hungryturn.jpg");
		atlasAlpha = Resources::Load<Mn::graphics::Texture>(L"Hungry_Guppy_Turn_Sprite_Alpha", L"..\\Resources\\Texture\\Fish\\guppy\\hungryturn_.jpg");
		at->Create(L"Hungry_Turn_Small", atlas, atlasAlpha, Vector2(0.0f, 0.0f), Vector2(80.0f, 80.f), 10, Vector2::Zero, 0.1);
		at->Create(L"Hungry_Turn_Middle", atlas, atlasAlpha,Vector2(0.0f, 80.0f), Vector2(80.0f, 80.f), 10, Vector2::Zero, 0.1);
		at->Create(L"Hungry_Turn_Large", atlas, atlasAlpha, Vector2(0.0f, 160.0f), Vector2(80.0f, 80.f), 10, Vector2::Zero, 0.1);
#pragma endregion
#pragma region Eat
		atlas = Resources::Load<Mn::graphics::Texture>(L"Guppy_Eat_Sprite", L"..\\Resources\\Texture\\Fish\\guppy\\smalleat.jpg");
		atlasAlpha = Resources::Load<Mn::graphics::Texture>(L"Guppy_Eat_Sprite_Alpha", L"..\\Resources\\Texture\\Fish\\guppy\\smalleat_.jpg");
		at->Create(L"Eat_Small", atlas, atlasAlpha, Vector2(0.0f, 0.0f), Vector2(80.0f, 80.f), 10, Vector2::Zero, 0.1);
		at->Create(L"Eat_Middle", atlas, atlasAlpha, Vector2(0.0f, 80.0f), Vector2(80.0f, 80.f), 10, Vector2::Zero, 0.1);
		at->Create(L"Eat_Large", atlas, atlasAlpha, Vector2(0.0f, 160.0f), Vector2(80.0f, 80.f), 10, Vector2::Zero, 0.1);

		atlas = Resources::Load<Mn::graphics::Texture>(L"Hungry_Guppy_Eat_Sprite", L"..\\Resources\\Texture\\Fish\\guppy\\hungryeat.jpg");
		atlasAlpha = Resources::Load<Mn::graphics::Texture>(L"Hungry_Guppy_Eat_Sprite_Alpha", L"..\\Resources\\Texture\\Fish\\guppy\\hungryeat_.jpg");
		at->Create(L"Hungry_Eat_Small", atlas, atlasAlpha, Vector2(0.0f, 0.0f), Vector2(80.0f, 80.f), 10, Vector2::Zero, 0.1);
		at->Create(L"Hungry_Eat_Middle", atlas, atlasAlpha, Vector2(0.0f, 80.0f), Vector2(80.0f, 80.f), 10, Vector2::Zero, 0.1);
		at->Create(L"Hungry_Eat_Large", atlas, atlasAlpha, Vector2(0.0f, 160.0f), Vector2(80.0f, 80.f), 10, Vector2::Zero, 0.1);
#pragma endregion
#pragma region Death
		atlas = Resources::Load<Mn::graphics::Texture>(L"Hungry_Guppy_Death_Sprite", L"..\\Resources\\Texture\\Fish\\guppy\\smalldie.jpg");
		atlasAlpha =  Resources::Load<Mn::graphics::Texture>(L"Hungry_Guppy_Death_Sprite_Alpha", L"..\\Resources\\Texture\\Fish\\guppy\\smalldie_.jpg");
		at->Create(L"Hungry_Death_Small", atlas, atlasAlpha, Vector2(0.0f, 0.0f), Vector2(80.0f, 80.f), 10, Vector2::Zero, 0.1);
		at->Create(L"Hungry_Death_Middle", atlas, atlasAlpha, Vector2(0.0f, 80.0f), Vector2(80.0f, 80.f), 10, Vector2::Zero, 0.1);
		at->Create(L"Hungry_Death_Large", atlas, atlasAlpha, Vector2(0.0f, 160.0f), Vector2(80.0f, 80.f), 10, Vector2::Zero, 0.1);
#pragma endregion
		at->PlayAnimation(L"Swim_Small", true);
#pragma endregion

	}
	void GuppyRender::Update()
	{
	}
	void GuppyRender::LateUpdate()
	{
	}
	void GuppyRender::Render()
	{
	}
	void GuppyRender::AfterTurn()
	{
		/*GuppyScript* gs =GetOwner()->GetComponent<GuppyScript>();
		GuppyAnimationCntrl* GAC = GetOwner()->GetComponent<GuppyAnimationCntrl>();*/

		//gs->SetBehavior(eBehavior::Swim);
		//GAC->Play();
	}
	void GuppyRender::EndTurn()
	{
	/*	GuppyScript* gs =GetOwner()->GetComponent<GuppyScript>();
		if (gs->GetDir() == eDir::Left)
			gs->SetDir(eDir::Right);
		else
			gs->SetDir(eDir::Left);*/

		//ConstantBuffer* cb = renderer::constantBuffer[(UINT)eCBType::Flip];
		//renderer::FlipCB data = {};
		//if (GetOwner()->GetComponent<GuppyScript>()->GetDir() == eDir::Right)
		//	data.FlipX = 1;
		//else
		//	data.FlipX = 0;
		//cb->setData(&data);
		//cb->Bind(eShaderStage::PS);
	}
}
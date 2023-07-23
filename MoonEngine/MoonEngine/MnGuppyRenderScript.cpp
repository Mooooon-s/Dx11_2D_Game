#include "MnGuppyRenderScript.h"
#include "MnGameObject.h"
#include "MnMeshRenderer.h"
#include "MnAnimator.h"
#include "MnResources.h"
#include "MnGuppy.h"

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
		at->PlayAnimation(L"Hungry_Swim_Middle", true);
#pragma endregion

	}
	void GuppyRender::Update()
	{
		Guppy* guppy = dynamic_cast<Guppy*>(GetOwner());
		eFishState state = guppy->GetFishState();
		if (state == _PreState)
			return;
	}
	void GuppyRender::LateUpdate()
	{
	}
	void GuppyRender::Render()
	{
	}
}
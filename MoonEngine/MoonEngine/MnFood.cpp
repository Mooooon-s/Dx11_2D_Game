#include "MnFood.h"
#include "MnMeshRenderer.h"
#include "MnResources.h"
#include "MnMaterial.h"
#include "MnAnimator.h"
#include "MnGameObject.h"
#include "MnCollider2D.h"
#include "MnFoodScript.h"
namespace Mn
{
	Food::Food()
		:_Level(1)
	{
	}
	Food::~Food()
	{
	}
	void Food::Initialize()
	{
		Collider2D* coll = AddComponent<Collider2D>();
		coll->SetSize(Vector2(0.2f, 0.2f));

		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"FoodSpriteAnimaionMaterial"));

		Animator* at = AddComponent<Animator>();

		std::shared_ptr<Mn::graphics::Texture> atlas
			= Resources::Load<Mn::graphics::Texture>(L"Food_Sprite", L"..\\Resources\\Texture\\Food\\food.jpg");
		std::shared_ptr<Mn::graphics::Texture> atlasAlpha
			= Resources::Load<Mn::graphics::Texture>(L"Food_Sprite_Alpha", L"..\\Resources\\Texture\\Food\\_food.jpg");

		at->Create(L"Level_1_Food", atlas, atlasAlpha, Vector2(0.0f, 0.0f), Vector2(40.0f, 40.f), 10, Vector2::Zero, 0.1);
		at->Create(L"Level_2_Food", atlas, atlasAlpha, Vector2(0.0f, 40.0f), Vector2(40.0f, 40.f), 10, Vector2::Zero, 0.1);
		at->Create(L"Level_3_Food", atlas, atlasAlpha, Vector2(0.0f, 80.0f), Vector2(40.0f, 40.f), 10, Vector2::Zero, 0.1);

		at->PlayAnimation(L"Level_1_Food", true);

		FoodScript* foodscript = AddComponent<FoodScript>();
		foodscript->Initialize();
	}
	void Food::Update()
	{
		GameObject::Update();
	}
	void Food::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void Food::Render()
	{
		GameObject::Render();
	}
}
#include "MnFoodIcon.h"

#include "MnSoundManager.h"
#include "MnSceneManager.h"
#include "MnMoney.h"

#include "MnMeshRenderer.h"
#include "MnResources.h"
#include "MnAnimator.h"
#include "MnAudioClip.h"

namespace Mn
{
	FoodIcon::FoodIcon()
		: _FoodLevel(1)
	{
	}
	FoodIcon::~FoodIcon()
	{
	}
	void FoodIcon::Initialize()
	{
		Transform* tr = GetComponent<Transform>();
		tr->Scale(0.4f, 0.4f, 0.0f);
		Vector3 pos = tr->Position();
		pos.y += 0.05;
		tr->Position(pos);

		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"SpriteAnimaionMaterial"));
		mr->FlipX(0);

		std::shared_ptr<Mn::graphics::Texture> atlas
			= Resources::Load< Mn::graphics::Texture>(L"Food_Icon_Sprite", L"..\\Resources\\Texture\\Food\\food.jpg");
		std::shared_ptr<Mn::graphics::Texture> atlasAlpha
			= Resources::Load<Mn::graphics::Texture>(L"Food_Icon_Sprite_Alpha", L"..\\Resources\\Texture\\Food\\_food.jpg");
		Animator* at = AddComponent<Animator>();
		at->Create(L"Level_1_Food", atlas, atlasAlpha, Vector2(0.0f, 0.0f), Vector2(40.0f, 40.f), 10, Vector2::Zero, 0.1);
		at->Create(L"Level_2_Food", atlas, atlasAlpha, Vector2(0.0f, 40.0f), Vector2(40.0f, 40.f), 10, Vector2::Zero, 0.1);
		at->Create(L"Level_3_Food", atlas, atlasAlpha, Vector2(0.0f, 80.0f), Vector2(40.0f, 40.f), 10, Vector2::Zero, 0.1);

		at->PlayAnimation(L"Level_1_Food", true);
	}
	void FoodIcon::Update()
	{
		GameObject::Update();
	}
	void FoodIcon::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void FoodIcon::Render()
	{
		GameObject::Render();
	}
	void FoodIcon::OnClick()
	{
		Animator* at = GetComponent<Animator>();
		SoundPlay();
		if (_FoodLevel == 1)
		{
			_FoodLevel++;
			at->PlayAnimation(L"Level_2_Food", true);
		}
		else if (_FoodLevel == 2)
		{
			_FoodLevel++;
			at->PlayAnimation(L"Level_3_Food", true);
		}
	}
	void FoodIcon::SoundPlay()
	{
		int flag = false;
		switch (_FoodLevel)
		{
		case 1:
		case 2:
			MnSoundManager::SoundPlay(L"ButtonSound_Buy");
			break;
		case 3:
			MnSoundManager::SoundPlay(L"Buzzer");
			for (auto obj : SceneManager::ActiveScene()->GetLayer(Mn::enums::eLayerType::UI).GetGameObjects()) {
				if (dynamic_cast<Money*>(obj) && !flag) {
					dynamic_cast<Money*>(obj)->EarnMoney(200);
					flag = true;
				}
				if (flag)
					break;
			}
			break;
		default:
			break;
		}
	}
}
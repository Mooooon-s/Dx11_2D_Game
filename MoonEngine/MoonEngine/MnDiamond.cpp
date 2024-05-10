#include "MnDiamond.h"
#include "MnDiamondRender.h"
#include "MnDiamondScript.h"
#include "MnSceneManager.h"
#include "MnMoney.h"

namespace Mn
{
	Diamond::Diamond()
		: _Price(200)
	{
	}
	Diamond::~Diamond()
	{
	}
	void Diamond::Initialize()
	{
		SetName(L"Diamond");
		Collider2D* coll = AddComponent<Collider2D>();
		coll->SetSize(Vector2(0.5, 0.5));

		Transform* tr = GetComponent<Transform>();
		tr->Scale(Vector3(0.5, 0.5, 0.0f));
		DiamondRender* DR = AddComponent<DiamondRender>();
		DiamondScript* DS = AddComponent<DiamondScript>();

		Resources::Load<Mn::AudioClip>(L"Get_Diamond", L"..\\Resources\\Sound\\diamond.wav");

		GameObject::Initialize();
	}
	void Diamond::Update()
	{
		GameObject::Update();
	}
	void Diamond::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void Diamond::Render()
	{
		GameObject::Render();
	}
	void Diamond::OnClick(Vector3 pos)
	{ 
		Scene* scene = SceneManager::ActiveScene();
		std::vector<GameObject*> gameObj = scene->GetLayer(eLayerType::UI).GetGameObjects();
		for (GameObject* obj : gameObj)
		{
			if (dynamic_cast<Money*>(obj))
			{
				dynamic_cast<Money*>(obj)->EarnMoney(_Price);
			}
		}
		Resources::Find<Mn::AudioClip>(L"Get_Diamond")->SoundPlay();
		this->State(eState::Dead);
	}
}
#include "MnCoin.h"
#include "MnTime.h"

#include "MnCollider2D.h"

#include "MnCoinRender.h"
#include "MnSceneManager.h"
#include "MnMoney.h"

namespace Mn
{
	Coin::Coin()
		: _Speed(0.3f)
		, _Time(0.0f)
		, _Price(15)
	{
	}
	Coin::~Coin()
	{
	}
	void Coin::Initialize()
	{
		SetName(L"Coin");
		Collider2D* coll = AddComponent<Collider2D>();
		coll->SetSize(Vector2(0.5, 0.5));

		Transform* tr = GetComponent<Transform>();
		tr->Scale(Vector3(0.5, 0.5, 0.0f));

		CoinRender* CR = AddComponent<CoinRender>();
		CR->SetLevel(_Level);

		LoadSound();
		
		GameObject::Initialize();
	}
	void Coin::Update()
	{
		Transform* tr = GetComponent<Transform>();
		Vector3 pos = tr->Position();
		pos += Vector3(0.0f, -1.0f, 0.0f) * _Speed * Time::DeltaTime();
		tr->Position(pos);
		GameObject::Update();
	}
	void Coin::LateUpdate()
	{
		Transform* tr = GetComponent<Transform>();
		Vector3 pos = tr->Position();
		if (pos.y <= -1.3f)
		{
			_Time += Time::DeltaTime();
			if (_Time >= 0.5)
			{
				this->State(GameObject::eState::Dead);
			}
		}
		GameObject::LateUpdate();
	}
	void Coin::Render()
	{
		GameObject::Render();
	}
	void Coin::OnClick(Vector3 pos)
	{
		Scene* scene = SceneManager::ActiveScene();
		std::vector<GameObject*> gameObj = scene->GetLayer(eLayerType::UI).GetGameObjects();
		for (GameObject* obj : gameObj)
		{
			if (dynamic_cast<Money*>(obj))
			{
				switch ((UINT)_Level)
				{
				case 2:
					_Price = 15;
					break;
				case 3:
					_Price = 35;
					break;
				case 4:
					_Price = 2000;
					break;
				default:
					break;
				}
				dynamic_cast<Money*>(obj)->EarnMoney(_Price);
			}
		}
		SoundPlay();
		this->State(eState::Dead);
	}
	void Coin::LoadSound()
	{
		Resources::Load<Mn::AudioClip>(L"Get_Coin", L"..\\Resources\\Sound\\POINTS.ogg");
		Resources::Load<Mn::AudioClip>(L"Get_TREASURE", L"..\\Resources\\Sound\\TREASURE.ogg");
	}
	void Coin::SoundPlay()
	{
		if(_Level < 4)
			Resources::Find<AudioClip>(L"Get_Coin")->SoundPlay();
		else
			Resources::Find<AudioClip>(L"Get_TREASURE")->SoundPlay();
	}
}
#include "MnCoin.h"
#include "MnTime.h"

#include "MnCollider2D.h"

#include "MnCoinRender.h"

namespace Mn
{
	Coin::Coin()
		: _Speed(0.3f)
		, _Time(0.0f)
	{
	}
	Coin::~Coin()
	{
	}
	void Coin::Initialize()
	{
		Collider2D* coll = AddComponent<Collider2D>();
		coll->SetSize(Vector2(0.5, 0.5));

		Transform* tr = GetComponent<Transform>();
		tr->Scale(Vector3(0.5, 0.5, 0.0f));

		CoinRender* CR = AddComponent<CoinRender>();
		CR->SetLevel(_Level);
		
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
		if (pos.y <= -1.5f)
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
	void Coin::Click()
	{
		this->State(eState::Dead);
	}
}
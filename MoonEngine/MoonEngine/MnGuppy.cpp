#include "MnGuppy.h"

#include "MnMeshRenderer.h"
#include "MnResources.h"
#include "MnTexture.h"
#include "MnAnimator.h"
#include "MnCollider2D.h"
#include "MnGuppyScript.h"

#include "MnGuppyRenderScript.h"
#include "MnGuppyAnimationCntrl.h"
#include "MnChomp.h"
#include "MnObject.h"

#include "MnTime.h"

namespace Mn
{
	Guppy::Guppy()
		: _Flag(2)
	{
	}
	Guppy::~Guppy()
	{
	}
	void Guppy::Initialize()
	{
		Transform* tr = GetComponent<Transform>();
		tr->Scale(Vector3(0.8, 0.8, 0.0f));
		SetName(L"Guppy");
		Collider2D* col = AddComponent<Collider2D>();
		col->SetSize(Vector2(0.25f, 0.25f));

		GuppyRender* GR = AddComponent<GuppyRender>();

		_GBT = AddComponent<GuppyBehaviorTree>();

		GameObject::Initialize();
	}
	void Guppy::Update()
	{
		DropIntoTank();
		if (_Flag == 2)
		{
			GameObject::Update();
		}
	}
	void Guppy::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void Guppy::Render()
	{
		GameObject::Render();
	}
	void Guppy::OnClick()
	{
		Transform* tr = GetComponent<Transform>();
		Vector3 pos = tr->Position();
		pos.z -= 0.01f;
		Chomp* chomp = object::Instantiate<Chomp>(pos, eLayerType::Effect);
		chomp->Initialize();

		this->State(GameObject::eState::Dead);
	}
	UINT Guppy::FishLevel()
	{
		return _GBT->GetGuppyLevel();
	}
	bool Guppy::FishStarving()
	{
		return _GBT->GetGuppyStarving();
	}
	void Guppy::DropIntoTank()
	{
		Transform* tr = GetComponent<Transform>();
		Vector3 pos = tr->Position();
		if (pos.y >= 0.6f && _Flag == 0)
		{
			pos.y -= 1.5 * Time::DeltaTime();
			tr->Position(pos);
		}
		else if (pos.y <= 0.6f && _Flag == 0)
			_Flag = 1;

		if (pos.y <= 0.8f && _Flag == 1)
		{
			pos.x += -0.5 * Time::DeltaTime();
			pos.y += 0.5 * Time::DeltaTime();
			tr->Position(pos);
		}
		else if (pos.y >= 0.8f && _Flag == 1)
			_Flag = 2;
	}
}
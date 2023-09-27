#include "MnGuppy.h"

#include "MnMeshRenderer.h"
#include "MnResources.h"
#include "MnTexture.h"
#include "MnAnimator.h"
#include "MnCollider2D.h"
#include "MnGuppyScript.h"

#include "MnGuppyRenderScript.h"
#include "MnGuppyAnimationCntrl.h"

#include "MnTime.h"

namespace Mn
{
	Guppy::Guppy()
		: _Flag(0)
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
		Transform* tr = GetComponent<Transform>();
		Vector3 pos = tr->Position();
		if (pos.y >= 0.8f && _Flag == 0)
		{
			pos.y -= 1.5 * Time::DeltaTime();
			tr->Position(pos);
		}
		else
		{
			_Flag = 1;
		}
		if(_Flag ==1)
			GameObject::Update();
	}
	void Guppy::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void Guppy::Render()
	{
		GameObject::Render();
	}
	UINT Guppy::FishLevel()
	{
		return _GBT->GetGuppyLevel();
	}
}
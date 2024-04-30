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

#include "MnBubbleParticle.h"

namespace Mn
{
	Guppy::Guppy()
		: _Flag(2)
		, _BP(nullptr)
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
		
		//if (_Flag != 2)
		//{
		//	Vector3 bubblepos = Vector3(tr->Position().x, tr->Position().y, tr->Position().z - 8.01);
		//	BubbleParticle * bp = object::Instantiate<BubbleParticle>(bubblepos, eLayerType::Particle);
		//	bp->SetTarget(this);
		//	bp->Initialize();
		//	//_BP = object::Instantiate<BubbleParticle>(bubblepos, eLayerType::Particle);
		//	//_BP->SetTarget(this);
		//	//_BP->Initialize();
		//}
		GameObject::Initialize();
	}
	void Guppy::Update()
	{
		if(_Flag!=2)
			DropIntoTank();
		else
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
		{
			_Flag = 2;
			//_BP->State(GameObject::eState::Dead);
		}
	}
}
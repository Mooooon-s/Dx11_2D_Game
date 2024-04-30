#include "MnBubbleParticle.h"
#include "MnParticleSystem.h"
#include "MnTime.h"


namespace Mn
{
	BubbleParticle::BubbleParticle()
		: _PS(nullptr)
		, _Time(0.f)
	{
	}
	BubbleParticle::~BubbleParticle()
	{
	}
	void BubbleParticle::Initialize()
	{
		Transform* tr = GetComponent<Transform>();
		_PS = AddComponent<ParticleSystem>(tr->Position());
	}
	void BubbleParticle::Update()
	{
		Transform* tr = _Target->GetComponent<Transform>();
		_PS->SetPosition(tr->Position());
		GameObject::Update();
	}
	void BubbleParticle::LateUpdate()
	{
		_Time += Time::DeltaTime();
		if (_Time >= 0.8f)
			this->State(eState::Dead);

		GameObject::LateUpdate();
	}
	void BubbleParticle::Render()
	{
		GameObject::Render();
	}
}
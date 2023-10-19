#include "MnBubbleParticle.h"
#include "MnParticleSystem.h"

namespace Mn
{
	BubbleParticle::BubbleParticle()
		: _PS(nullptr)
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
		GameObject::LateUpdate();
	}
	void BubbleParticle::Render()
	{
		GameObject::Render();
	}
}
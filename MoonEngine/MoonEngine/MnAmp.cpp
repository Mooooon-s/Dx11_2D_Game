#include "MnAmp.h"
#include "MnAmpRender.h"


namespace Mn
{
	Amp::Amp()
		: _ABT(nullptr)
	{
	}
	Amp::~Amp()
	{
	}
	void Amp::Initialize()
	{
		AmpRender* AR = AddComponent<AmpRender>();
		_ABT = AddComponent<AmpBehaviorTree>();
		GameObject::Initialize();
	}
	void Amp::Update()
	{
		GameObject::Update();
	}
	void Amp::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void Amp::Render()
	{
		GameObject::Render();
	}
	void Amp::OnClick(Vector3 pos)
	{
		_ABT->OnClick();
	}
}
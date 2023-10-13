#include "MnTailFlop.h"
#include "MnTailFlopRender.h"

namespace Mn
{
	TailFlop::TailFlop()
	{
	}
	TailFlop::~TailFlop()
	{
	}
	void TailFlop::Initialize()
	{
		TailFlopRender* TFR = AddComponent<TailFlopRender>();
		TFR->Initialize();
	}
	void TailFlop::Update()
	{
		GameObject::Update();
	}
	void TailFlop::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void TailFlop::Render()
	{
		GameObject::Render();
	}
}
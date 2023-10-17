#include "MnGus.h"
#include "MnGusRender.h"
#include "MnGusBehaviorTree.h"

namespace Mn
{
	Gus::Gus()
	{
	}
	Gus::~Gus()
	{
	}
	void Gus::Initialize()
	{
		GusRender* GR = AddComponent<GusRender>();
		GusBehaviorTree* GBT = AddComponent<GusBehaviorTree>();
		GameObject::Initialize();
	}
	void Gus::Update()
	{
		GameObject::Update();
	}
	void Gus::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void Gus::Render()
	{
		GameObject::Render();
	}
}
#include "MnZorf.h"
#include "MnZorfRender.h"
#include "MnZorfBehaviorTree.h"

namespace Mn
{
	Zorf::Zorf()
	{
	}
	Zorf::~Zorf()
	{
	}
	void Zorf::Initialize()
	{
		ZorfRender* ZR = AddComponent<ZorfRender>();
		ZorfBehaviorTree* ZBT = AddComponent<ZorfBehaviorTree>();
		GameObject::Initialize();
	}
	void Zorf::Update()
	{
		GameObject::Update();
	}
	void Zorf::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void Zorf::Render()
	{
		GameObject::Render();
	}
}
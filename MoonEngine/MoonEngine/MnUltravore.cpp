#include "MnUltravore.h"
#include "MnUltravoreRender.h"
#include "MnUltravoreBehaviorTree.h"

namespace Mn
{
	Ultravore::Ultravore()
	{
	}
	Ultravore::~Ultravore()
	{
	}
	void Ultravore::Initialize()
	{
		UltravoreRender* UVR = AddComponent<UltravoreRender>();
		UltravoreBehaviorTree* UVBT = AddComponent<UltravoreBehaviorTree>();
		GameObject::Initialize();
	}
	void Ultravore::Update()
	{
		GameObject::Update();
	}
	void Ultravore::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void Ultravore::Render()
	{
		GameObject::Render();
	}
	void Ultravore::OnClick(Vector3 pos)
	{
	}
}

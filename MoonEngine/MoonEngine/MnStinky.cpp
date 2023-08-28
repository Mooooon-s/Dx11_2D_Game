#include "MnStinky.h"
#include "MnStinkyRenderScript.h"
#include "MnStinkyBehaviorTree.h"

namespace Mn
{
	Stinky::Stinky()
	{
	}
	Stinky::~Stinky()
	{
	}
	void Stinky::Initialize()
	{
		Transform* tr = GetComponent<Transform>();
		tr->Scale(Vector3(0.5f, 0.5f, 0.0f));
		StinkyRenderScript* SRS = AddComponent<StinkyRenderScript>();
		StinkyBehaviorTree* SBT = AddComponent<StinkyBehaviorTree>();

		GameObject::Initialize();
	}
	void Stinky::Update()
	{
		GameObject::Update();
	}
	void Stinky::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void Stinky::Render()
	{
		GameObject::Render();
	}
}
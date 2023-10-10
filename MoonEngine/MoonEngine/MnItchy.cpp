#include "MnItchy.h"
#include "MnItchyRender.h"
#include "MnItchyBehaviorTree.h"

namespace Mn
{
	Itchy::Itchy()
	{
	}
	Itchy::~Itchy()
	{
	}
	void Itchy::Initialize()
	{
		ItchyRender* IR = AddComponent<ItchyRender>();
		ItchyBehaviorTree* IBT = AddComponent<ItchyBehaviorTree>();
		GameObject::Initialize();
	}
	void Itchy::Update()
	{
		GameObject::Update();
	}
	void Itchy::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void Itchy::Render()
	{
		GameObject::Render();
	}
}
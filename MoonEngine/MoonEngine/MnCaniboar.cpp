#include "MnCaniboar.h"
#include "MnCaniboarRender.h"
#include "MnCaniboarBehaviorTree.h"

namespace Mn
{
	Caniboar::Caniboar()
		: _Flag(0)
	{
	}
	Caniboar::~Caniboar()
	{
	}
	void Caniboar::Initialize()
	{
		Transform* tr = GetComponent<Transform>();
		tr->Scale(Vector3(0.5, 0.5, 0.0f));
		SetName(L"CaniBoar");
		CaniboarRender* CR = AddComponent<CaniboarRender>();

		CaniboarBehaviorTree* CBT = AddComponent<CaniboarBehaviorTree>();
		
		GameObject::Initialize();
	}
	void Caniboar::Update()
	{
		GameObject::Update();
	}
	void Caniboar::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void Caniboar::Render()
	{
		GameObject::Render();
	}
}
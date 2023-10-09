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

		Collider2D* col = AddComponent<Collider2D>();
		col->SetSize(Vector2(0.3f, 0.3f));

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
	void Caniboar::OnClick()
	{
		this->State(GameObject::eState::Dead);
	}
}
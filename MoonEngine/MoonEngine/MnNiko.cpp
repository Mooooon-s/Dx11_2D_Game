#include "MnNiko.h"
#include "MnNikoRenderer.h"
#include "MnNikoScript.h"
#include "MnCollider2D.h"
#include "MnAnimator.h"

namespace Mn
{
	Niko::Niko()
	{
	}
	Niko::~Niko()
	{
	}
	void Niko::Initialize()
	{
		Collider2D* coll = AddComponent<Collider2D>();
		coll->SetSize(Vector2(0.5f, 0.5f));

		Transform* tr = GetComponent<Transform>();
		tr->Scale(Vector3(0.6f, 0.6f, 0.0f));
		NikoRenderer* NR = AddComponent<NikoRenderer>();
		NikoScript* NS = AddComponent<NikoScript>();
		GameObject::Initialize();
	}
	void Niko::Update()
	{
		GameObject::Update();
	}
	void Niko::LateUpdate()
	{
		GameObject:: LateUpdate();
	}
	void Niko::Render()
	{
		GameObject::Render();
	}
	void Niko::OnClick()
	{
		//NikoScript* NS = GetComponent<NikoScript>();
		//NS->OnClick();
	}
	void Niko::OnClick(Vector3 pos)
	{
		NikoScript* NS = GetComponent<NikoScript>();
		NS->OnClick();
	}
}
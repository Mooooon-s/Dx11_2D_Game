#include "MnNiko.h"
#include "MnNikoRenderer.h"
#include "MnNikoScript.h"

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
		Transform* tr = GetComponent<Transform>();
		tr->Scale(Vector3(0.8f, 0.8f, 0.0f));
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
}
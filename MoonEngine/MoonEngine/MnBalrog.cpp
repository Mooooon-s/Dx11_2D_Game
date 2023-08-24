#include "MnBalrog.h"
#include "MnBalrogRenderScript.h"

namespace Mn
{
	Balrog::Balrog()
	{
	}
	Balrog::~Balrog()
	{
	}
	void Balrog::Initialize()
	{
		BalrogRenderScript* BRS = AddComponent<BalrogRenderScript>();

		GameObject::Initialize();
	}
	void Balrog::Update()
	{
		GameObject::Update();
	}
	void Balrog::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void Balrog::Render()
	{
		GameObject::Render();
	}
	void Balrog::Click()
	{
	}
}

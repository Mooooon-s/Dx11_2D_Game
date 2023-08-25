#include "MnPearl.h"
#include "MnPearlScript.h"

namespace Mn
{
	Pearl::Pearl()
	{
	}
	Pearl::~Pearl()
	{
	}
	void Pearl::Initialize()
	{
		PearlScript* ps = AddComponent<PearlScript>();
		GameObject::Initialize();
	}
	void Pearl::Update()
	{
		GameObject::Update();
	}
	void Pearl::LateUpdate()
	{
		GameObject::LateUpdate();
	}
}
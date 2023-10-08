#include "MnSylv.h"
#include "MnSylvRender.h"
#include "MnBalrogBehaviorTree.h"

namespace Mn
{
	Sylv::Sylv()
	{
	}
	Sylv::~Sylv()
	{
	}
	void Sylv::Initialize()
	{
		SylvRender* SR = AddComponent<SylvRender>();
		GameObject::Initialize();
	}
	void Sylv::Update()
	{
		GameObject::Update();
	}
	void Sylv::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void Sylv::Render()
	{
		GameObject::Render();
	}
	void Sylv::OnClick(Vector3 pos)
	{
	}
}
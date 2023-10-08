#include "MnSylv.h"
#include "MnSylvRender.h"
#include "MnSylvBehaviorTree.h"

namespace Mn
{
	Sylv::Sylv()
		: _SBT(nullptr)
	{
	}
	Sylv::~Sylv()
	{
	}
	void Sylv::Initialize()
	{
		SylvRender* SR = AddComponent<SylvRender>();
		_SBT = AddComponent<SylvBehaviorTree>();
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
		_SBT->OnClick(pos);
	}
}
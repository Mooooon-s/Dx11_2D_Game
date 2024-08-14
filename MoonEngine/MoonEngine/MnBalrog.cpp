#include "MnBalrog.h"
#include "MnBalrogRenderScript.h"
#include "MnSoundManager.h"

namespace Mn
{
	Balrog::Balrog()
		:_BHT(nullptr)
	{
	}
	Balrog::~Balrog()
	{
	}
	void Balrog::Initialize()
	{
		BalrogRenderScript* BRS = AddComponent<BalrogRenderScript>();
		_BHT = AddComponent<BalrogBehaviorTree>();
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
	void Balrog::OnClick(Vector3 pos)
	{
		MnSoundManager::SoundPlay(L"Hit_Sound");
		_BHT->OnClick(pos);
	}
}

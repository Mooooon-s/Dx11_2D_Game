#include "MnInGameButton.h"
#include "MnButtonFrame.h"
#include "MnButtonPanel.h"
#include "MnObject.h"

namespace Mn
{
	InGameButton::InGameButton()
	{
	}
	InGameButton::~InGameButton()
	{
	}
	void InGameButton::Initialize()
	{
		Transform* tr = GetComponent<Transform>();
		Vector3 pos = tr->Position();
		ButtonFrame* BF = object::Instantiate<ButtonFrame>(pos, eLayerType::UI);
		pos.z += 0.01;
		ButtonPanel* BP = object::Instantiate<ButtonPanel>(pos, eLayerType::UI);
		BF->Initialize();
		BP->Initialize();
	}
	void InGameButton::Update()
	{
		GameObject::Update();
	}
	void InGameButton::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void InGameButton::Render()
	{
		GameObject::Render();
	}
	void InGameButton::OnClick()
	{
	}
	void InGameButton::MouseOn()
	{
	}
}
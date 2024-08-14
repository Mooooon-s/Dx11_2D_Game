#include "MnGameStartButton.h"
#include "MnStartButtonRender.h"
#include "MnObject.h"

namespace Mn
{
	GameStartButton::GameStartButton()
	{
	}
	GameStartButton::~GameStartButton()
	{
	}
	void GameStartButton::Initialize()
	{
		StartButtonRender* SBR = AddComponent<StartButtonRender>();
		SBR->Initialize();

	}
	void GameStartButton::Update()
	{
		GameObject::Update();
	}
	void GameStartButton::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void GameStartButton::Render()
	{
		GameObject::Render();
	}
	void GameStartButton::OnClick()
	{
	}
	void GameStartButton::OnClick(Vector3 pos)
	{
	}
	void GameStartButton::MouseOn()
	{
	}
	void GameStartButton::MouseOff()
	{
	}
}
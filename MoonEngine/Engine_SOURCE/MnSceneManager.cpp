#include "MnSceneManager.h"
#include "playScene.h"

namespace Mn
{
	Scene* SceneManager::_ActiveScene = nullptr;
	void SceneManager::Initialize()
	{
		_ActiveScene = new playScene();
		_ActiveScene->Initialize();
	}
	void SceneManager::Update()
	{
		_ActiveScene->Update();
	}
	void SceneManager::LateUpdate()
	{
		_ActiveScene->LateUpdate();
	}
	void SceneManager::Render()
	{
		_ActiveScene->Render();
	}
}
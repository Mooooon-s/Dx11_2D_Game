#include "MnSceneManager.h"
#include "playScene.h"

namespace Mn
{
	Scene* SceneManager::_ActiveScene = nullptr;
	std::map<std::wstring, Scene* > SceneManager::_Scenes;
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
	Scene* SceneManager::LoadScene(std::wstring name)
	{
		std::map<std::wstring, Scene*>::iterator iter 
			= _Scenes.find(name);
		
		if (iter == _Scenes.end())
			return nullptr;

		_ActiveScene->OnExit();
		_ActiveScene = iter->second;
		_ActiveScene->OnEnter();

		return iter->second;
	}
}
#include "MnSceneManager.h"
#include "playScene.h"
#include "MnTitleScene.h"
#include "MnInput.h"

namespace Mn
{
	Scene* SceneManager::_ActiveScene = nullptr;
	std::map<std::wstring, Scene* > SceneManager::_Scenes;
	void SceneManager::Initialize()
	{
		_ActiveScene = new playScene();
		_Scenes.insert(std::make_pair(L"playScene", _ActiveScene));
		TitleScene* title = new TitleScene();
		_Scenes.insert(std::make_pair(L"titleScene", title));
		_ActiveScene->Initialize();
		title->Initialize();
	}
	void SceneManager::Update()
	{
		if (Input::GetKeyDown(eKeyCode::P))
		{
			_ActiveScene = _Scenes.find(L"titleScene")->second;
		}
		if (Input::GetKeyDown(eKeyCode::O))
		{
			_ActiveScene = _Scenes.find(L"playScene")->second;
		}
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
	void SceneManager::Release()
	{
		for (auto iter : _Scenes)
		{
			delete iter.second;
			iter.second = nullptr;
		}
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
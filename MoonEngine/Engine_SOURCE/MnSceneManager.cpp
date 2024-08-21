#include "MnSceneManager.h"
#include "MnTitleScene.h"
#include "MnInput.h"

namespace Mn
{
	Scene* SceneManager::_ActiveScene = nullptr;
	std::map<std::wstring, Scene* > SceneManager::_Scenes;
	void SceneManager::Initialize()
	{

	}
	void SceneManager::Update()
	{
		if (Input::GetKeyDown(eKeyCode::P))
		{
			LoadScene(L"TitleScene");
		}
		if (Input::GetKeyDown(eKeyCode::O))
		{
			LoadScene(L"PlayScene");
		}
		if (Input::GetKeyDown(eKeyCode::I))
		{
			LoadScene(L"MenuScene");
		}
		if (Input::GetKeyDown(eKeyCode::U)) {
			LoadScene(L"EndingScene");
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
	void SceneManager::FontRender()
	{
		_ActiveScene->FontRender();
	}
	void SceneManager::Destroy()
	{
		_ActiveScene->Destroy();
	}
	void SceneManager::Release()
	{
		for (auto& iter : _Scenes)
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
#pragma once
#include "../Engine_SOURCE/MnSceneManager.h"

#ifdef _DEBUG
#pragma comment(lib, "..\\x64\\Debug\\MoonEngine.lib")
#else
#pragma comment(lib, "..\\x64\\Release\\MoonEngine.lib")
#endif

#include "playScene.h"
#include "MnTitleScene.h"
#include "MnMenuScene.h"

namespace Mn
{
	void InitializeScenes()
	{
		SceneManager::CreateScene<playScene>(L"PlayScene");
		SceneManager::CreateScene<MenuScene>(L"MenuScene");
		SceneManager::CreateScene<TitleScene>(L"TitleScene");
	}
}
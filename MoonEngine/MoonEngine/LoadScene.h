#pragma once
#include "../Engine_SOURCE/MnSceneManager.h"
#include "playScene.h"
#include "MnTitleScene.h"


#ifdef _DEBUG
#pragma comment(lib, "..\\x64\\Debug\\MoonEngine.lib")
#else
#pragma comment(lib, "..\\x64\\Release\\MoonEngine.lib")
#endif

namespace Mn
{
	void InitializeScenes()
	{
		//PlayScene* playScene = new PlayScene();
		SceneManager::CreateScene<playScene>(L"PlayScene");
	}
}
#pragma once
#include "../Engine_SOURCE/MnSceneManager.h"
#include "playScene.h"
#include "MnTitleScene.h"
#include "MnCaveStage.h"
#include "MnCaveStageBoss.h"
#include "MnForestStageBoss.h"


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
		SceneManager::CreateScene<ForestStageBoss>(L"ForestStageBoss");
		SceneManager::CreateScene<TitleScene>(L"TitleScene");
		SceneManager::CreateScene<CaveStage>(L"CaveStage");
		SceneManager::CreateScene<CaveStageBoss>(L"CaveStageBoss");
	}
}
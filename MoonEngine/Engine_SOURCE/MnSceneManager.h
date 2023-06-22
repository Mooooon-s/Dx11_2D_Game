#pragma once
#include "MnScene.h"

namespace Mn
{
	class SceneManager
	{
	private:
		static Scene* _ActiveScene;
		static std::map<std::wstring, Scene* > _Scenes;
	
	public:
		static void Initialize();
		static void Update();
		static void LateUpdate();
		static void Render();
		static void Release();
	
		static Scene* LoadScene(std::wstring name);
	public:
		static Scene* ActiveScene() { return _ActiveScene; }
	};
}

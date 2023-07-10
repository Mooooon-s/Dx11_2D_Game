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
		static void Destroy();
		static void Release();

		template <typename T>
		static bool CreateScene(std::wstring name)
		{
			T* scene = new T();

			std::map<std::wstring, Scene*>::iterator iter = _Scenes.find(name);

			if (iter != _Scenes.end())
				return false;

			_Scenes.insert(std::make_pair(name, scene));
			_ActiveScene = scene;
			scene->Initialize();
			return true;
		}
	
		static Scene* LoadScene(std::wstring name);

	public:
		static Scene* ActiveScene() { return _ActiveScene; }
	};
}

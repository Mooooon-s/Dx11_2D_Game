#include "MnScene.h"
#include "MnSceneManager.h"

namespace Mn
{
	Scene::Scene()
	{
		_Layers.resize((int)Mn::enums::eLayerType::End);
	}
	Scene::~Scene()
	{
	}
	void Scene::Initialize()
	{
	}
	void Scene::Update()
	{
		for (Layer& layer : _Layers)
		{
			layer.Update();
		}
	}
	void Scene::LateUpdate()
	{
		for (Layer& layer : _Layers)
		{
			layer.LateUpdate();
		}
	}
	void Scene::Render()
	{
		for (Layer& layer : _Layers)
		{
			layer.Render();
		}
	}
	void Scene::FontRender()
	{
		for (Layer& layer : _Layers)
		{
			layer.FontRender();
		}
	}
	void Scene::Destroy()
	{
		for (Layer& layer : _Layers)
		{
			layer.Destroy();
		}
	}
	void Scene::OnEnter()
	{
	}
	void Scene::OnExit()
	{
	}
	void Scene::AddGameObject(eLayerType type, GameObject* gameObj)
	{
		_Layers[(int)type].AddGameObject(gameObj);
	}
}
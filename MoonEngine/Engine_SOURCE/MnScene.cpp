#include "MnScene.h"

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
		for (auto layer : _Layers)
		{
			layer.Initialize();
		}
	}
	void Scene::Update()
	{
		for (auto layer : _Layers)
		{
			layer.Update();
		}
	}
	void Scene::LateUpdate()
	{
		for (auto layer : _Layers)
		{
			layer.LateUpdate();
		}
	}
	void Scene::Render()
	{
		for (auto layer : _Layers)
		{
			layer.Render();
		}
	}
	void Scene::AddGameObject(eLayerType type, GameObject* gameObj)
	{
		_Layers[(int)type].AddGameObject(gameObj);
	}
}
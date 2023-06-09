#include "MnScene.h"

namespace Mn
{
	Scene::Scene()
	{
	}
	Scene::~Scene()
	{
	}
	void Scene::Initialize()
	{

	}
	void Scene::Update()
	{
		for (auto gameObj : _GameObjects)
		{
			gameObj->Update();
		}
	}
	void Scene::LateUpdate()
	{
	}
	void Scene::Render()
	{
		for (auto gameObj : _GameObjects)
		{
			gameObj->Render();
		}
	}
}
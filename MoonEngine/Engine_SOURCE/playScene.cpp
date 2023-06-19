#include "playScene.h"
#include "MnGameObject.h"

Mn::playScene::playScene()
{
}

Mn::playScene::~playScene()
{
}

void Mn::playScene::Initialize()
{
	GameObject* player = new GameObject();
	AddGameObject(eLayerType::Player, player);

	Scene::Initialize();
}

void Mn::playScene::Update()
{
	Scene::Update();
}

void Mn::playScene::LateUpdate()
{
	Scene::LateUpdate();
}

void Mn::playScene::Render()
{
	Scene::Render();
}

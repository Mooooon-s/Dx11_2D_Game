#include "playScene.h"
#include "MnGameObject.h"
#include "MnTransform.h"
#include "MnMeshRenderer.h"
#include "MnMesh.h"
#include "MnResources.h"
#include "MnCameraScript.h"

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
	MeshRenderer* mr = player->AddComponent<MeshRenderer>();
	mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
	mr->SetMaterial(Resources::Find<Material>(L"SpriteMaterial"));

	player->AddComponent<CameraScript>();

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

#include "playScene.h"
#include "MnGameObject.h"
#include "MnTransform.h"
#include "MnMeshRenderer.h"
#include "MnMesh.h"
#include "MnResources.h"
#include "MnCameraScript.h"
#include "MnCamera.h"
#include "MnMainCharacter.h"

Mn::playScene::playScene()
{
}

Mn::playScene::~playScene()
{
}

void Mn::playScene::Initialize()
{

	GameObject* background = new GameObject();
	AddGameObject(eLayerType::Player, background);
	MeshRenderer* BGmr = background->AddComponent<MeshRenderer>();
	BGmr->SetMesh(Resources::Find<Mesh>(L"BackGroundMesh"));
	BGmr->SetMaterial(Resources::Find<Material>(L"BackGroundMaterial_Layer_0"));
	background->GetComponent<Transform>()->Position(Vector3(0.0f, 0.0f, 2.0f));

	MainCharacter* player = new MainCharacter();
	AddGameObject(eLayerType::Player, player);
	MeshRenderer* mr = player->AddComponent<MeshRenderer>();
	mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
	mr->SetMaterial(Resources::Find<Material>(L"SpriteMaterial"));
	player->GetComponent<Transform>()->Position(Vector3(0.0f, 0.0f, 1.0f));


	GameObject* camera = new GameObject();
	AddGameObject(eLayerType::Player, camera);
	camera->GetComponent<Transform>()->Position(Vector3(0.0f, 0.0f, -10.0f));
	Camera* cameraComp = camera->AddComponent<Camera>();
	camera->AddComponent<CameraScript>();

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

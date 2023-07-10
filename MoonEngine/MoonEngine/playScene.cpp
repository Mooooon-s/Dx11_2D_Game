#include "playScene.h"
#include "MnGameObject.h"
#include "MnTransform.h"
#include "MnMeshRenderer.h"
#include "MnMesh.h"
#include "MnResources.h"
#include "MnCameraScript.h"
#include "MnCamera.h"
#include "MnMainCharacter.h"
#include "MnWaterScript.h"
#include "MnPlayerHp.h"
#include "MnPlayerScript.h"
#include "MnGridScript.h"
#include "MnObject.h"
#include "MnForestBG.h"

#define PI 3.1415926535

Mn::playScene::playScene()
{
}

Mn::playScene::~playScene()
{
}

void Mn::playScene::Initialize()
{
	MainCharacter* player = object::Instantiate<MainCharacter>(eLayerType::Player);
	player->Initialize();
	player->AddComponent<PlayerScript>();

	
	ForestBG* background = object::Instantiate<ForestBG>(eLayerType::BackGround);
	background->Initialize();

	//Main Camera
	GameObject* camera = new GameObject();
	AddGameObject(eLayerType::Player, camera);
	camera->GetComponent<Transform>()->Position(Vector3(0.0f, 0.0f, -10.0f));
	Camera* cameraComp = camera->AddComponent<Camera>();
	CameraScript* cs = camera->AddComponent<CameraScript>();
	cs->SetTarget(player);
	cameraComp->TurnLayerMask(eLayerType::UI, false);
	cameraComp->TurnLayerMask(eLayerType::Water);

	GameObject* water = new GameObject();
	AddGameObject(eLayerType::Water, water);
	MeshRenderer* waterMr = water->AddComponent<MeshRenderer>();
	waterMr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
	waterMr->SetMaterial(Resources::Find<Material>(L"WaterMaterial"));
	water->GetComponent<Transform>()->Position(Vector3(0.0f, -0.8f, 1.0f));
	water->AddComponent<WaterScript>();

	GameObject* grid = new GameObject();
	grid->SetName(L"Grid");
	AddGameObject(eLayerType::Grid, grid);
	MeshRenderer* mr = grid->AddComponent<MeshRenderer>();
	mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
	mr->SetMaterial(Resources::Find<Material>(L"GridMaterial"));
	GridScript* gridSc = grid->AddComponent<GridScript>();
	gridSc->SetCamera(cameraComp);

	GameObject* UICam = new GameObject();
	AddGameObject(eLayerType::UI, UICam);
	Camera* camComp = UICam->AddComponent<Camera>();
	camComp->DisableLayerMasks();
	camComp->TurnLayerMask(eLayerType::UI, true);
	
	PlayerHp* hpBar = new PlayerHp(this);
	AddGameObject(eLayerType::UI, hpBar);
	hpBar->Initialize();
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

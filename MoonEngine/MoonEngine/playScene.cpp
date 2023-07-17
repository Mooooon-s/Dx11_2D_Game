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
#include "MnPumpkin.h"
#include "../Engine_SOURCE/MnKdTree.h"
#include "MnRenderer.h"
#include "MnCollisionManager.h"

#define PI 3.1415926535

Mn::playScene::playScene()
{
}

Mn::playScene::~playScene()
{
}

void Mn::playScene::Initialize()
{
	CollisionManager::SetLayer(eLayerType::Player, eLayerType::Monster, true);


	_KdTree = new KdTree(1);

	MainCharacter* player = object::Instantiate<MainCharacter>(eLayerType::Player);
	player->Initialize();
	player->AddComponent<PlayerScript>();
	player->SetName(L"player");

	
	ForestBG* background = object::Instantiate<ForestBG>(eLayerType::BackGround);
	background->Initialize();

	Pumpkin* pumpkinMon = object::Instantiate<Pumpkin>(Vector3(0.0f,0.5f,0.0f),eLayerType::Monster);
	pumpkinMon->Initialize();
	pumpkinMon->SetName(L"Mon");
	//Pumpkin* pumpkinMon1 = object::Instantiate<Pumpkin>(Vector3(0.5f, 0.5f, 0.0f),eLayerType::Monster);
	//pumpkinMon1->Initialize();
	//pumpkinMon1->SetName(L"Mon");
	//Pumpkin* pumpkinMon2 = object::Instantiate<Pumpkin>(Vector3(-0.5f, 0.5f, 0.0f),eLayerType::Monster);
	//pumpkinMon2->Initialize();
	//pumpkinMon2->SetName(L"Mon");
	//Pumpkin* pumpkinMon3 = object::Instantiate<Pumpkin>(Vector3(-0.5f, -0.5f, 0.0f), eLayerType::Monster);
	//pumpkinMon3->Initialize();
	//pumpkinMon3->SetName(L"Mon");

	//Main Camera
	GameObject* camera = new GameObject();
	AddGameObject(eLayerType::UI, camera);
	camera->GetComponent<Transform>()->Position(Vector3(0.0f, 0.0f, -10.0f));
	Camera* cameraComp = camera->AddComponent<Camera>();
	CameraScript* cs = camera->AddComponent<CameraScript>();
	//cs->SetTarget(player);
	cameraComp->TurnLayerMask(eLayerType::UI, false);
	cameraComp->TurnLayerMask(eLayerType::Water);
	renderer::cameras.push_back(cameraComp);
	renderer::mainCamera = cameraComp;

	GameObject* water = new GameObject();
	AddGameObject(eLayerType::Water, water);
	MeshRenderer* waterMr = water->AddComponent<MeshRenderer>();
	waterMr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
	waterMr->SetMaterial(Resources::Find<Material>(L"WaterMaterial"));
	water->GetComponent<Transform>()->Position(Vector3(0.0f, -0.8f, 1.0f));
	water->AddComponent<WaterScript>();

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
	Scene* scene = SceneManager::ActiveScene();
	for (auto a : scene->GetLayer(eLayerType::Monster).GetGameObjects())
	{
		_ActiveObjs.push_back(a);
	}
	_KdTree->BuildTree(_ActiveObjs);

	Scene::Update();
}

void Mn::playScene::LateUpdate()
{
	Scene::LateUpdate();
	_ActiveObjs.clear();
}

void Mn::playScene::Render()
{
	Scene::Render();
	
}

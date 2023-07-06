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

#define PI 3.1415926535

Mn::playScene::playScene()
{
}

Mn::playScene::~playScene()
{
}

void Mn::playScene::Initialize()
{
	MainCharacter* player = new MainCharacter();
	AddGameObject(eLayerType::Player, player);
	player->Initialize();

	GameObject* background = new GameObject();
	AddGameObject(eLayerType::BackGround, background);
	MeshRenderer* BGmr = background->AddComponent<MeshRenderer>();
	BGmr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
	BGmr->SetMaterial(Resources::Find<Material>(L"BackGroundMaterial_Layer_0"));
	BGmr->GetMaterial()->GetTexture()->CalculateRatio();
	Vector2 v = BGmr->GetMaterial()->GetTexture()->Raitio();
	background->GetComponent<Transform>()->Position(Vector3(0.0f, 0.0f, 2.0f));
	background->GetComponent<Transform>()->Scale(Vector3(v.x*4.5, v.y*4.5, 1.0f));


	GameObject* water = new GameObject();
	AddGameObject(eLayerType::Water, water);
	MeshRenderer* waterMr = water->AddComponent<MeshRenderer>();
	waterMr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
	waterMr->SetMaterial(Resources::Find<Material>(L"WaterMaterial"));
	water->GetComponent<Transform>()->Position(Vector3(0.0f, -0.8f, 1.0f));
	water->AddComponent<WaterScript>();

	GameObject* camera = new GameObject();
	AddGameObject(eLayerType::Player, camera);
	camera->GetComponent<Transform>()->Position(Vector3(0.0f, 0.0f, -10.0f));
	Camera* cameraComp = camera->AddComponent<Camera>();
	camera->AddComponent<CameraScript>();
	cameraComp->TurnLayerMask(eLayerType::UI, false);
	cameraComp->TurnLayerMask(eLayerType::Water, false);



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

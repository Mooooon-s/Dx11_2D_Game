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
	Transform* tr = player->GetComponent<Transform>();
	tr->Scale(Vector3(1.5,1.5f,1.5f));
	MeshRenderer* mr = player->AddComponent<MeshRenderer>();
	mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
	mr->SetMaterial(Resources::Find<Material>(L"SpriteMaterial"));
	player->GetComponent<Transform>()->Position(Vector3(0.0f, 0.0f, 0.0f));


	GameObject* background = new GameObject();
	AddGameObject(eLayerType::BackGround, background);
	MeshRenderer* BGmr = background->AddComponent<MeshRenderer>();
	BGmr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
	BGmr->SetMaterial(Resources::Find<Material>(L"BackGroundMaterial_Layer_0"));
	background->GetComponent<Transform>()->Position(Vector3(0.0f, 0.0f, 2.0f));

	GameObject* water = new GameObject();
	AddGameObject(eLayerType::Water, water);
	MeshRenderer* waterMr = water->AddComponent<MeshRenderer>();
	waterMr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
	waterMr->SetMaterial(Resources::Find<Material>(L"WaterMaterial"));
	water->GetComponent<Transform>()->Position(Vector3(0.0f, -0.8f, 1.0f));
	water->AddComponent<WaterScript>();




	GameObject* wcamera = new GameObject();
	AddGameObject(eLayerType::Player, wcamera);
	wcamera->GetComponent<Transform>()->Position(Vector3(0.0f, 0.0f, -10.0f));
	Camera* wcameraComp = wcamera->AddComponent<Camera>();
	wcamera->AddComponent<CameraScript>();
	wcameraComp->DisableLayerMasks();
	wcameraComp->TurnLayerMask(eLayerType::Water, true);

	GameObject* WaterCam = new GameObject();
	AddGameObject(eLayerType::Monster, WaterCam);
	Camera* wc = WaterCam->AddComponent<Camera>();
	float r = PI;
	wc->TurnLayerMask(eLayerType::Water, false);
	wc->TurnLayerMask(eLayerType::UI, false);
	WaterCam->GetComponent<Transform>()->Rotation(Vector3(r, r, 0.0f));
	WaterCam->GetComponent<Transform>()->Position(Vector3(0.0f, -1.0, 0.3f));

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
	
	GameObject* HpBar = new GameObject();
	AddGameObject(eLayerType::UI, HpBar);
	MeshRenderer* hpBarMr = HpBar->AddComponent<MeshRenderer>();
	hpBarMr->SetMesh(Resources::Find<Mesh>(L"BackGroundMesh"));
	hpBarMr->SetMaterial(Resources::Find<Material>(L"Hp_Bar"));

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

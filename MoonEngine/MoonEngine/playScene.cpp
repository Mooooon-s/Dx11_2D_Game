#include "playScene.h"


#include "../Engine_SOURCE/MnKdTree.h"

#include "MnCollisionManager.h"
#include "MnResources.h"

#include "MnGameObject.h"
#include "MnObject.h"
#include "MnTransform.h"
#include "MnMeshRenderer.h"
#include "MnMesh.h"
#include "MnCamera.h"
#include "MnRenderer.h"

#include "MnAquarimBG.h"
#include "MnTopBar.h"


#include "MnGuppy.h"

#include "MnCameraScript.h"
#include "MnGridScript.h"
#include "MnMouse.h"
#include "MnLight.h"


namespace Mn
{
	KdTree* kdTree = nullptr;

}


Mn::playScene::playScene()
{
}

Mn::playScene::~playScene()
{

}

void Mn::playScene::Initialize()
{
	kdTree = new KdTree(1);

	Guppy* guppy = object::Instantiate<Guppy>(eLayerType::Fish);
	guppy->Initialize();

	AquarimBG* aquarimBG = object::Instantiate<AquarimBG>(eLayerType::BackGround,enums::eAquarim::Stage1);
	aquarimBG->Initialize();

	TopBar* topbar = object::Instantiate<TopBar>(eLayerType::UI);
	topbar->Initialize();

	GameObject* light = new GameObject();
	light->SetName(L"Light");
	AddGameObject(eLayerType::Light, light);
	Light* lightComp = light->AddComponent<Light>();
	lightComp->SetType(eLightType::Directional);
	lightComp->SetColor(Vector4(1.0f, 1.0f, 1.0f, 1.0f));

	//Main Camera
	GameObject* camera = new GameObject();
	AddGameObject(eLayerType::UI, camera);
	camera->GetComponent<Transform>()->Position(Vector3(0.0f, 0.0f, -10.0f));
	Camera* cameraComp = camera->AddComponent<Camera>();
	CameraScript* cs = camera->AddComponent<CameraScript>();
	cameraComp->TurnLayerMask(eLayerType::UI, false);
	renderer::cameras.push_back(cameraComp);
	renderer::mainCamera = cameraComp;

	GameObject* UICam = new GameObject();
	UICam->SetName(L"UICam");
	AddGameObject(eLayerType::UI, UICam);
	Camera* camComp = UICam->AddComponent<Camera>();
	camComp->DisableLayerMasks();
	camComp->TurnLayerMask(eLayerType::UI, true);

	Mouse* mouse = object::Instantiate<Mouse>(eLayerType::UI);
	mouse->UICamera(camera);
	mouse->Initialize();
}

void Mn::playScene::Update()
{
	Scene* scene = SceneManager::ActiveScene();
	for (auto a : scene->GetLayer(eLayerType::Food).GetGameObjects())
	{
		_ActiveObjs.push_back(a);
	}
	kdTree->BuildTree(_ActiveObjs);
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

void Mn::playScene::Destroy()
{
}

void Mn::playScene::OnEnter()
{
}

void Mn::playScene::OnExit()
{
}

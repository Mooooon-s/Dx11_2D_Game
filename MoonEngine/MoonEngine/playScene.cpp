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

Mn::playScene::playScene()
	: _KdTree(nullptr)
{
}

Mn::playScene::~playScene()
{

}

void Mn::playScene::Initialize()
{
	_KdTree = new KdTree(1);

	Guppy* guppy = object::Instantiate<Guppy>(eLayerType::Fish);
	guppy->Initialize();

	AquarimBG* aquarimBG = object::Instantiate<AquarimBG>(eLayerType::BackGround,enums::eAquarim::Stage1);
	aquarimBG->Initialize();

	TopBar* topbar = object::Instantiate<TopBar>(eLayerType::UI);
	topbar->Initialize();


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
	AddGameObject(eLayerType::UI, UICam);
	Camera* camComp = UICam->AddComponent<Camera>();
	camComp->DisableLayerMasks();
	camComp->TurnLayerMask(eLayerType::UI, true);
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

void Mn::playScene::Destroy()
{
}

void Mn::playScene::OnEnter()
{
}

void Mn::playScene::OnExit()
{
}

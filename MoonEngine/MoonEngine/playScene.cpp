#include "playScene.h"
#include "MnComputeShader.h"
#include "MnPaintShader.h"
#include "MnParticleSystem.h"

#include "MnMoney.h"

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

#include "MnBalrog.h"

#include "MnGuppy.h"

#include "MnCameraScript.h"
#include "MnGridScript.h"
#include "MnMouse.h"
#include "MnLight.h"

#include "MnNiko.h"
#include "MnStinky.h"

#include "MnEventManager.h"
#include "MnInGameButton.h"

#include "MnCaniboar.h"

namespace Mn
{
	KdTree* kdTree = nullptr;
	KdTree* GuppyTree = nullptr;
}


Mn::playScene::playScene()
{
}

Mn::playScene::~playScene()
{

}

void Mn::playScene::Initialize()
{
	std::shared_ptr<PaintShader> paintShader = Resources::Find<PaintShader>(L"PaintShader");
	std::shared_ptr<Mn::graphics::Texture> paintTexture = Resources::Find<Mn::graphics::Texture>(L"PaintTexuture");
	paintShader->SetTarget(paintTexture);
	paintShader->OnExcute();

	kdTree = new KdTree(1);
	GuppyTree = new KdTree(1);

	Guppy* guppy2 = object::Instantiate<Guppy>(Vector3(1.5f,0.0f,0.01f),eLayerType::Fish);
	guppy2->Initialize();

	Guppy* guppy3 = object::Instantiate<Guppy>(Vector3(1.0f, 1.0f, 0.02f),eLayerType::Fish);
	guppy3->Initialize();

	Caniboar* cani = object::Instantiate<Caniboar>(Vector3(0.0f, 0.0f, 1.0f), eLayerType::Fish);
	cani->Initialize();

	Niko* niko = object::Instantiate<Niko>(Vector3(-1.4f,-0.4f,100.0f),eLayerType::Pet);
	niko->Initialize();

	Stinky* stinky = object::Instantiate<Stinky>(Vector3(0.0f,-1.2f,100.1f),eLayerType::Pet);
	stinky->Initialize();

	Money* money = object::Instantiate<Money>(eLayerType::UI);
	money->Initialize();

	AquarimBG* aquarimBG = object::Instantiate<AquarimBG>(eLayerType::BackGround,enums::eAquarim::Stage1);
	aquarimBG->Initialize();

	TopBar* topbar = object::Instantiate<TopBar>(eLayerType::UI);
	topbar->Initialize();


	//GameObject* particle = new GameObject();
	//particle->SetName(L"Particle");
	//AddGameObject(eLayerType::Particle, particle);
	//ParticleSystem* mr = particle->AddComponent<ParticleSystem>();
	//particle->GetComponent<Transform>()->Position(Vector3(0.0f, 0.0f, 1.0f));
	//particle->GetComponent<Transform>()->Scale(Vector3(0.2f, 0.2f, 0.2f));

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

	EventManager* eventmanager = object::Instantiate<EventManager>(eLayerType::UI);
	eventmanager->Initialize();

}

void Mn::playScene::Update()
{
	Scene* scene = SceneManager::ActiveScene();
	for (auto a : scene->GetLayer(eLayerType::Food).GetGameObjects())
	{
		if(a->State()==GameObject::eState::Active)
			_ActiveObjs.push_back(a);
	}
	kdTree->BuildTree(_ActiveObjs);

	for (auto guppy : scene->GetLayer(eLayerType::Fish).GetGameObjects())
	{
		if (guppy->State() == GameObject::eState::Active && dynamic_cast<Guppy*>(guppy)!=nullptr)
			_GuppyObjs.push_back(guppy);
	}
	GuppyTree->BuildTree(_GuppyObjs);

	Scene::Update();
}

void Mn::playScene::LateUpdate()
{
	Scene::LateUpdate();
	_ActiveObjs.clear();
	_GuppyObjs.clear();
}

void Mn::playScene::Render()
{
	Scene::Render();
}

void Mn::playScene::Destroy()
{
	Scene::Destroy();
}

void Mn::playScene::OnEnter()
{
	CollisionManager::SetLayer(eLayerType::Fish, eLayerType::Food, true);
	CollisionManager::SetLayer(eLayerType::Pet, eLayerType::Coin, true);
}

void Mn::playScene::OnExit()
{
}

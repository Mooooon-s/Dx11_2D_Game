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

#include "MnCameraScript.h"
#include "MnWaterScript.h"
#include "MnPlayerScript.h"
#include "MnGridScript.h"

#include "MnPumpkin.h"
#include "MnMainCharacter.h"

#include "MnForestBG.h"
#include "MnForestTree.h"
#include "MnForestLight.h"
#include "MnForestGround.h"

#include "MnPlayerHp.h"
#include "MnHpBar.h"
#include "MnHpFrame.h"

#define PI 3.1415926535

Mn::playScene::playScene()
{
}

Mn::playScene::~playScene()
{
}

void Mn::playScene::Initialize()
{
	_KdTree = new KdTree(1);

	CollisionManager::SetLayer(eLayerType::Player, eLayerType::Monster, true);


	ForestBG* background = object::Instantiate<ForestBG>(eLayerType::BackGround);
	background->Initialize();
	background->SetName(L"background");

	ForestTree* backgroundtree = object::Instantiate<ForestTree>(eLayerType::BackGround);
	backgroundtree->Initialize();
	background->SetName(L"background_Tree");

	ForestLight* backgroundLight = object::Instantiate<ForestLight>(eLayerType::BackGround);
	backgroundLight->Initialize();

	ForestGround* backfroundGround = object::Instantiate<ForestGround>(eLayerType::BackGround);
	backfroundGround->Initialize();

	MainCharacter* player = object::Instantiate<MainCharacter>(eLayerType::Player);
	player->Initialize();
	player->AddComponent<PlayerScript>();
	player->SetName(L"player");

	Pumpkin* pumpkinMon = object::Instantiate<Pumpkin>(Vector3(0.0f,0.5f,0.0f),eLayerType::Monster);
	pumpkinMon->Initialize();
	pumpkinMon->SetName(L"Mon");
	pumpkinMon->GetComponent<Transform>()->Rotation(Vector3(0.0f, 0.0f, 5.0f));





	//Main Camera
	GameObject* camera = new GameObject();
	AddGameObject(eLayerType::UI, camera);
	camera->GetComponent<Transform>()->Position(Vector3(0.0f, 0.0f, -10.0f));
	Camera* cameraComp = camera->AddComponent<Camera>();
	CameraScript* cs = camera->AddComponent<CameraScript>();
	cs->SetTarget(player);
	cameraComp->TurnLayerMask(eLayerType::UI, false);
	renderer::cameras.push_back(cameraComp);
	renderer::mainCamera = cameraComp;

	GameObject* UICam = new GameObject();
	AddGameObject(eLayerType::UI, UICam);
	Camera* camComp = UICam->AddComponent<Camera>();
	camComp->DisableLayerMasks();
	camComp->TurnLayerMask(eLayerType::UI, true);

	HpBar* hpbar = new HpBar(this);
	AddGameObject(eLayerType::UI, hpbar);
	hpbar->Initialize();
	Transform* hptr = hpbar->GetComponent<Transform>();

	PlayerHp* hpProgressBar = new PlayerHp(this);
	AddGameObject(eLayerType::UI, hpProgressBar);
	Transform* pHptr = hpProgressBar->GetComponent<Transform>();
	pHptr->SetParent(hptr);
	hpProgressBar->Initialize();

	HpFrame* hpFrame = new HpFrame(this);
	AddGameObject(eLayerType::UI, hpFrame);
	Transform* fHptr = hpFrame->GetComponent<Transform>();
	fHptr->SetParent(hptr);
	hpFrame->Initialize();

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

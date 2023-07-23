#include "MnMenuScene.h"
#include "MnObject.h"
#include "MnCameraScript.h"
#include "MnCamera.h"
#include "MnRenderer.h"


#include "MnMenuBG.h"

namespace Mn
{
	MenuScene::MenuScene()
	{
	}
	MenuScene::~MenuScene()
	{
	}
	void MenuScene::Initialize()
	{
		MenuBG* BG = object::Instantiate<MenuBG>(eLayerType::BackGround);
		BG->Initialize();

		//Main Camera
		GameObject* camera = new GameObject();
		AddGameObject(eLayerType::UI, camera);
		camera->GetComponent<Transform>()->Position(Vector3(0.0f, 0.0f, -10.0f));
		Camera* cameraComp = camera->AddComponent<Camera>();
		CameraScript* cs = camera->AddComponent<CameraScript>();
		cameraComp->TurnLayerMask(eLayerType::UI, false);
		renderer::cameras.push_back(cameraComp);
		renderer::mainCamera = cameraComp;

	}
	void MenuScene::Update()
	{
		Scene::Update();
	}
	void MenuScene::LateUpdate()
	{
		Scene::LateUpdate();
	}
	void MenuScene::Render()
	{
		Scene::Render();
	}
	void MenuScene::OnEnter()
	{

	}
	void MenuScene::OnExit()
	{

	}
}
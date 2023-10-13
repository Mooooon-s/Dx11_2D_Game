#include "MnMenuScene.h"
#include "MnObject.h"
#include "MnCameraScript.h"
#include "MnCamera.h"
#include "MnRenderer.h"
#include "MnMouse.h"
#include "MnPlayButton.h"

#include "MnMenuBG.h"

#include "MnPaintShader.h"
#include "MnResources.h"

#include "MnTailFlop.h"

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
		SetName(L"TitleScene");
		MenuBG* BG = object::Instantiate<MenuBG>(eLayerType::BackGround);
		BG->Initialize();

		PlayButton* PB = object::Instantiate<PlayButton>(Vector3(1.1f,1.2f,-1.0f), eLayerType::Button);
		PB->Initialize();

		TailFlop* TF = object::Instantiate<TailFlop>(Vector3(0.0f,0.0f,-1.0f),eLayerType::BackGround);
		TF->Initialize();
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
		//Main Camera
		GameObject* camera = new GameObject();
		AddGameObject(eLayerType::UI, camera);
		camera->GetComponent<Transform>()->Position(Vector3(0.0f, 0.0f, -10.0f));
		Camera* cameraComp = camera->AddComponent<Camera>();
		CameraScript* cs = camera->AddComponent<CameraScript>();
		cameraComp->TurnLayerMask(eLayerType::UI, false);
		renderer::cameras.push_back(cameraComp);
		renderer::mainCamera = cameraComp;

		Mouse* mouse = object::Instantiate<Mouse>(eLayerType::UI);
		mouse->UICamera(camera);
		mouse->Initialize();
	}
	void MenuScene::OnExit()
	{

	}
}
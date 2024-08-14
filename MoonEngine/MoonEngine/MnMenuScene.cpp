#include "MnAudioClip.h"
#include "MnCamera.h"
#include "MnCameraScript.h"
#include "MnMenuBG.h"
#include "MnMenuScene.h"
#include "MnMouse.h"
#include "MnObject.h"
#include "MnPaintShader.h"
#include "MnPlayButton.h"
#include "MnRenderer.h"
#include "MnResources.h"
#include "MnSoundManager.h"
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
		SetName(L"MenuScene");

		MenuBG* BG = object::Instantiate<MenuBG>(eLayerType::BackGround);
		BG->Initialize();

		PlayButton* PB = object::Instantiate<PlayButton>(Vector3(1.1f,1.2f,-1.0f), eLayerType::Button);
		PB->Initialize();

		TailFlop* TF = object::Instantiate<TailFlop>(Vector3(-1.21f,-1.10f,-1.0f),eLayerType::Effect);
		TF->Initialize();

		//Main Camera
		GameObject* camera = new GameObject();
		camera->SetName(L"MenuCamera");
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

		GameObject* light = new GameObject();
		light->SetName(L"Light");
		AddGameObject(eLayerType::Light, light);
		Light* lightComp = light->AddComponent<Light>();
		lightComp->SetType(eLightType::Directional);
		lightComp->SetColor(Vector4(1.0f, 1.0f, 1.0f, 1.0f));
		lightComp->SetScene(this->GetName());
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
		MnSoundManager::SoundPlay(L"Menu_Music",0.5f,true);
	}
	void MenuScene::OnExit()
	{
		MnSoundManager::SoundStop(L"Menu_Music");
	}
}
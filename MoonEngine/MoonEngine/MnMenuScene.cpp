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

#include "MnAudioClip.h"

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

		//std::shared_ptr<PaintShader> paintShader = Resources::Find<PaintShader>(L"PaintShader");
		//std::shared_ptr<Mn::graphics::Texture> paintTexture = Resources::Find<Mn::graphics::Texture>(L"PaintTexuture");
		//paintShader->SetTarget(paintTexture);
		//paintShader->OnExcute();

		Resources::Load<Mn::AudioClip>(L"Menu_Music", L"..\\Resources\\music\\Menu.mp3");

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
		Resources::Find<Mn::AudioClip>(L"Menu_Music")->SoundPlay();
	}
	void MenuScene::OnExit()
	{
		Resources::Find<Mn::AudioClip>(L"Menu_Music")->Stop();
	}
}
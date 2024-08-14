#include "MnTitleScene.h"
#include "MnGameObject.h"
#include "MnMaterial.h"
#include "MnMeshRenderer.h"
#include "MnResources.h"
#include "MnTransform.h"
#include "MnObject.h"

#include "MnRenderer.h"
#include "MnCameraScript.h"
#include "MnTransform.h"

#include "MnInput.h"
#include "MnSceneManager.h"
#include "MnSoundManager.h"

#include "MnGameStartButton.h"
#include "StartButtonBarRender.h"

#include "MnMouse.h"

#include "MnAudioClip.h"

namespace Mn
{
	TitleScene::TitleScene()
	{
	}
	TitleScene::~TitleScene()
	{
	}
	void TitleScene::Initialize()
	{
		MnSoundManager::SoundPlay(L"TitleBackground",0.3f);


		SetName(L"TitleScene");
		GameObject* titleScene = new GameObject();
		AddGameObject(eLayerType::BackGround, titleScene);
		MeshRenderer* tmr = titleScene->AddComponent<MeshRenderer>();
		tmr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		tmr->SetMaterial(Resources::Find<Material>(L"TitleMaterial"));
		tmr->GetMaterial()->CalcurateRatio();
		Vector2 v = tmr->GetMaterial()->GetTexture()->Raitio();
		titleScene->GetComponent<Transform>()->Position(Vector3(0.0f, 0.0f, 2.0f));
		titleScene->GetComponent<Transform>()->Scale(Vector3(v.x * 3.55, v.y * 3.55, 1.0f));

		GameStartButton* GSB = object::Instantiate<GameStartButton>(Vector3(0.0f,0.0f,-1.1f), eLayerType::Button);
		GSB->Initialize();

		StartButtonBarRender* SBBR = object::Instantiate<StartButtonBarRender>(Vector3(0.0f, 0.0f, -1.0f), eLayerType::Button);
		SBBR->Initialize();

		//Main Camera
		GameObject* camera = new GameObject();
		camera->SetName(L"TitleCamera");
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
	void TitleScene::Update()
	{
		Scene::Update();
		if (Input::GetKeyDown(eKeyCode::I))
		{
			SceneManager::LoadScene(L"MenuScene");
		}
	}
	void TitleScene::LateUpdate()
	{
		Scene::LateUpdate();
	}
	void TitleScene::Render()
	{
		Scene::Render();
	}
	void TitleScene::Destroy()
	{
		Scene::Destroy();
	}
	void TitleScene::OnEnter()
	{
		MnSoundManager::SoundPlay(L"TitleBackground");
	}
	void TitleScene::OnExit()
	{
		MnSoundManager::SoundStop(L"TitleBackground");
	}
}
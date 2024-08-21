#include "MnCameraScript.h"
#include "MnCreateIcon.h"
#include "MnEndingScene.h"
#include "MnGuppyIcon.h"
#include "MnRenderer.h"
#include "MnResources.h"
#include "MnSoundManager.h"
#include "MnFontWrapper.h"
#include "MnCaniboarIcon.h"
#include "MnUltravoreIcon.h"
#include "MnAmpIcon.h"
#include "MnZorfIcon.h"
#include "MnNikoIcon.h"
#include "MnStinkyIcon.h"
#include "MnPregoIcon.h"

namespace Mn
{
	EndingScene::EndingScene()
		: _szFloat(L"Thankyou for Playing!")
	{
	}
	EndingScene::~EndingScene()
	{
	}
	void EndingScene::Initialize()
	{
		SetName(L"EndingScene");
		GameObject* titleScene = new GameObject();
		AddGameObject(eLayerType::BackGround, titleScene);
		MeshRenderer* tmr = titleScene->AddComponent<MeshRenderer>();
		tmr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		tmr->SetMaterial(Resources::Find<Material>(L"EndingSceneMaterial"));
		tmr->GetMaterial()->CalcurateRatio();
		Vector2 v = tmr->GetMaterial()->GetTexture()->Raitio();
		titleScene->GetComponent<Transform>()->Position(Vector3(0.0f, 0.0f, 2.0f));
		titleScene->GetComponent<Transform>()->Scale(Vector3(v.x * 5.0f, v.y * 3.55, 0.0f));

		//Main Camera
		GameObject* camera = new GameObject();
		AddGameObject(eLayerType::UI, camera);
		camera->GetComponent<Transform>()->Position(Vector3(0.0f, 0.0f, -10.0f));
		Camera* cameraComp = camera->AddComponent<Camera>();
		CameraScript* cs = camera->AddComponent<CameraScript>();
		cameraComp->TurnLayerMask(eLayerType::UI, true);
		renderer::cameras.push_back(cameraComp);
		renderer::mainCamera = cameraComp;

		GameObject* light = new GameObject();
		light->SetName(L"Light");
		AddGameObject(eLayerType::Light, light);
		Light* lightComp = light->AddComponent<Light>();
		lightComp->SetType(eLightType::Directional);
		lightComp->SetColor(Vector4(1.0f, 1.0f, 1.0f, 1.0f));
		lightComp->SetScene(this->GetName());

		MakeIcon();

	}
	void EndingScene::MakeIcon()
	{
		GameObject* icon = CreateIcon<GuppyIcon>(Vector3(0.0f, 0.0f, -9.7f));
		icon->Initialize();

		GameObject* caniboar = CreateIcon<CaniboarIcon>(Vector3(0.2f, 0.0f, -9.6f));
		caniboar->Initialize();

		GameObject* ultra = CreateIcon<UltravoreIcon>(Vector3(0.4f, 0.0f, -9.5f));
		ultra->Initialize();

		GameObject* zorf = CreateIcon<ZorfIcon>(Vector3(0.6f, 0.0f, -9.4f));
		zorf->Initialize();

		GameObject* niko = CreateIcon<NikoIcon>(Vector3(0.8f, 0.0f, -9.3f));
		niko->Initialize();

		GameObject* amp = CreateIcon<AmpIcon>(Vector3(1.0f, 0.0f, -9.2f));
		amp->Initialize();

		GameObject* stinky = CreateIcon<StinkyIcon>(Vector3(1.2f, 0.0f, -9.1f));
		stinky->Initialize();

		GameObject* prego = CreateIcon<PregoIcon>(Vector3(1.3f, 0.0f, -9.0f));
		prego->Initialize();
	}
	void EndingScene::Update()
	{
		Scene::Update();
	}
	void EndingScene::LateUpdate()
	{
		Scene::LateUpdate();
	}
	void EndingScene::Render()
	{
		Scene::Render();
	}
	void EndingScene::FontRender()
	{
		FontWrapper::DrawFont(_szFloat, 300, 100, 40, FONT_RGBA(255, 0, 255, 255));
	}
	void EndingScene::Destroy()
	{
		Scene::Destroy();
	}
	void EndingScene::OnEnter()
	{
		MnSoundManager::SoundPlay(L"Ending_Music",0.5,true);
	}
	void EndingScene::OnExit()
	{
		MnSoundManager::SoundStop(L"Ending_Music");
	}
}
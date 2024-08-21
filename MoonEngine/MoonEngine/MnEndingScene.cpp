#include "../Engine_SOURCE/MnApplication.h"

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

extern Mn::Application application;

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
		_Cam = new GameObject();
		AddGameObject(eLayerType::UI, _Cam);
		_Cam->GetComponent<Transform>()->Position(Vector3(0.0f, 0.0f, -10.0f));
		Camera* cameraComp = _Cam->AddComponent<Camera>();
		CameraScript* cs = _Cam->AddComponent<CameraScript>();
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
		icon->GetComponent<Transform>()->Scale(Vector3(0.8, 0.8, 0.0f));
		Obj.insert(std::make_pair(L"guppy", icon));

		GameObject* caniboar = CreateIcon<CaniboarIcon>(Vector3(0.5f, 0.0f, -9.6f));
		caniboar->Initialize();
		caniboar->GetComponent<Transform>()->Scale(Vector3(0.5, 0.5, 0.0f));
		Obj.insert(std::make_pair(L"boar", caniboar));

		GameObject* ultra = CreateIcon<UltravoreIcon>(Vector3(1.f, 0.0f, -9.5f));
		ultra->Initialize();
		ultra->GetComponent<Transform>()->Scale(Vector3(0.5, 0.5, 0.0f));
		Obj.insert(std::make_pair(L"Ultra", ultra));

		GameObject* zorf = CreateIcon<ZorfIcon>(Vector3(0.6f, 0.0f, -9.4f));
		zorf->Initialize();
		zorf->GetComponent<Transform>()->Scale(Vector3(0.5f, 0.5f, 0.0f));

		GameObject* niko = CreateIcon<NikoIcon>(Vector3(0.8f, 0.0f, -9.3f));
		niko->Initialize();
		niko->GetComponent<Transform>()->Scale(Vector3(0.5f, 0.5f, 0.0f));

		GameObject* amp = CreateIcon<AmpIcon>(Vector3(1.0f, 0.0f, -9.2f));
		amp->Initialize();
		amp->GetComponent<Transform>()->Scale(Vector3(1.0f, 0.5f, 0.0f));

		GameObject* stinky = CreateIcon<StinkyIcon>(Vector3(1.2f, 0.0f, -9.1f));
		stinky->Initialize();
		stinky->GetComponent<Transform>()->Scale(Vector3(0.5f, 0.5f, 0.0f));

		GameObject* prego = CreateIcon<PregoIcon>(Vector3(1.3f, 0.0f, -9.0f));
		prego->Initialize();
		prego->GetComponent<Transform>()->Scale(Vector3(0.5f, 0.5f, 0.0f));
	}

	void EndingScene::CalulatePos(GameObject* _obj)
	{
		Transform* tr = _Cam->GetComponent<Transform>();

		// 변환하고자 하는 월드 좌표
		Vector3 worldPos = _obj->GetComponent<Transform>()->Position();
		Matrix world = tr->WorldMatrix();
		Matrix view = tr->ViewMatrix();
		Matrix projection = tr->ProjectionMatrix();

		// 월드 좌표를 클립 공간 좌표로 변환
		Vector3 clipSpacePos = XMVector3TransformCoord(worldPos, world * view * projection);

		clipSpacePos.z = 0.f;
			
			//Vector3::TransformCoord();

		// 클립 공간 좌표를 뷰포트 좌표(스크린 좌표)로 변환
		Viewport viewport;
		viewport.width = application.GetWidth();
		viewport.height = application.GetHeight();
		viewport.x = 0;
		viewport.y = 0;
		viewport.minDepth = 0.0f;
		viewport.maxDepth = 1.0f;

		Vector3 screenPos = viewport.Project(clipSpacePos, projection, view, Matrix::Identity);

		FontWrapper::DrawFont((const wchar_t*)_obj->GetName().c_str(), screenPos.x - _obj->GetName().size(), screenPos.y + 40, 20, FONT_RGBA(255, 0, 255, 255));

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

		for (auto o : Obj) {
			CalulatePos(o.second);
		}
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
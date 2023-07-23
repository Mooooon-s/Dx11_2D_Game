#include "MnTitleScene.h"
#include "MnGameObject.h"
#include "MnMaterial.h"
#include "MnMeshRenderer.h"
#include "MnResources.h"
#include "MnTransform.h"
#include "MnMainCharacter.h"
#include "MnObject.h"

#include "MnRenderer.h"
#include "MnCameraScript.h"
#include "MnTransform.h"

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
		GameObject* titleScene = new GameObject();
		AddGameObject(eLayerType::BackGround, titleScene);
		MeshRenderer* tmr = titleScene->AddComponent<MeshRenderer>();
		tmr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		tmr->SetMaterial(Resources::Find<Material>(L"TitleMaterial"));
		tmr->GetMaterial()->CalcurateRatio();
		Vector2 v = tmr->GetMaterial()->GetTexture()->Raitio();
		titleScene->GetComponent<Transform>()->Position(Vector3(0.0f, 0.0f, 2.0f));
		titleScene->GetComponent<Transform>()->Scale(Vector3(v.x * 3.55, v.y * 3.55, 1.0f));

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
	void TitleScene::Update()
	{
		Scene::Update();
	}
	void TitleScene::LateUpdate()
	{
		Scene::LateUpdate();
	}
	void TitleScene::Render()
	{
		Scene::Render();
	}
	void TitleScene::OnEnter()
	{
	}
	void TitleScene::OnExit()
	{
	}
}
#include "MnCaveStage.h"

#include "../Engine_SOURCE/MnKdTree.h"

#include "MnObject.h"
#include "MnMainCharacter.h"

#include "MnCamera.h"
#include "MnCameraScript.h"
#include "MnRenderer.h"

#include "MnCaveBG.h"

#include "MnHpBar.h"
#include "MnHpFrame.h"
#include "MnPlayerHp.h"

namespace Mn
{
	CaveStage::CaveStage()
	{
	}
	CaveStage::~CaveStage()
	{
	}
	void CaveStage::Initialize()
	{
		CaveBG* caveBG = new CaveBG(this);
		caveBG->Initialize();

		//Main Camera
		GameObject* camera = new GameObject();
		AddGameObject(eLayerType::UI, camera);
		camera->GetComponent<Transform>()->Position(Vector3(0.0f, 0.0f, -10.0f));
		Camera* cameraComp = camera->AddComponent<Camera>();
		CameraScript* cs = camera->AddComponent<CameraScript>();
		//cs->SetTarget(player);
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
	void CaveStage::Update()
	{
		Scene::Update();
	}
	void CaveStage::LateUpdate()
	{
		Scene::LateUpdate();
	}
	void CaveStage::Render()
	{
		Scene::Render();
	}
	void CaveStage::Destroy()
	{
	}
	void CaveStage::OnEnter()
	{
	}
	void CaveStage::OnExit()
	{
	}
}
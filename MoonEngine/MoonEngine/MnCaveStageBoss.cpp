#include "MnCaveStageBoss.h"

#include "../Engine_SOURCE/MnKdTree.h"

#include "MnObject.h"
#include "MnCaveBossBG.h"

#include "MnCameraScript.h"
#include "MnRenderer.h"
#include "MnCaveWall.h"

#include "MnPlayerHp.h"
#include "MnHpBar.h"
#include "MnHpFrame.h"

namespace Mn
{
	CaveStageBoss::CaveStageBoss()
	{
	}
	CaveStageBoss::~CaveStageBoss()
	{
	}
	void CaveStageBoss::Initialize()
	{
		CaveBossBG* background = object::Instantiate<CaveBossBG>(eLayerType::BackGround);
		background->Initialize();

		CaveWall* caveWall = object::Instantiate<CaveWall>(eLayerType::BackGround);
		caveWall->Initialize();

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
	void CaveStageBoss::Update()
	{
		Scene::Update();
	}
	void CaveStageBoss::LateUpdate()
	{
		Scene::LateUpdate();
	}
	void CaveStageBoss::Render()
	{
		Scene::Render();
	}
	void CaveStageBoss::Destroy()
	{
	}
	void CaveStageBoss::OnEnter()
	{
	}
	void CaveStageBoss::OnExit()
	{
	}
}
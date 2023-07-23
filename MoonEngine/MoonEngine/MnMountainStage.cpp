#include "MnMountainStage.h"
#include "MnMeshRenderer.h"
#include "MnResources.h"
#include "MnCamera.h"
#include "MnCameraScript.h"
#include "MnRenderer.h"
#include "MnHpBar.h"
#include "MnPlayerHp.h"
#include "MnHpFrame.h"

namespace Mn
{
	MountainStage::MountainStage()
	{

	}
	MountainStage::~MountainStage()
	{

	}
	void MountainStage::Initialize()
	{
		GameObject* MountainBackGround = new GameObject();
		MeshRenderer* mr = MountainBackGround->AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"BackGround_Mounain_1"));
		AddGameObject(eLayerType::BackGround, MountainBackGround);
		mr->GetMaterial()->GetTexture()->CalculateRatio();
		Vector2 v = mr->GetMaterial()->GetTexture()->Raitio();
		MountainBackGround->GetComponent<Transform>()->Position(Vector3(0.0f, 0.0f, 2.9f));
		MountainBackGround->GetComponent<Transform>()->Scale(Vector3(v.x * 4.5, v.y * 4.5, 1.0f));

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
	void MountainStage::Update()
	{
		Scene::Update();
	}
	void MountainStage::LateUpdate()
	{
		Scene::LateUpdate();
	}
	void MountainStage::Render()
	{
		Scene::Render();
	}
	void MountainStage::Destroy()
	{

	}
	void MountainStage::OnEnter()
	{

	}
	void MountainStage::OnExit()
	{

	}
}
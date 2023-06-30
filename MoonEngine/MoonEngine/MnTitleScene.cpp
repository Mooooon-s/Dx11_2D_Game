#include "MnTitleScene.h"
#include "MnGameObject.h"
#include "MnMaterial.h"
#include "MnMeshRenderer.h"
#include "MnResources.h"
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
		GameObject* background = new GameObject();
		AddGameObject(eLayerType::BackGround, background);
		MeshRenderer* mr = background->AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"BackGroundMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"BackGroundMaterial_Layer_1"));
		background->GetComponent<Transform>()->Position(Vector3(0.0f, 0.0f, 0.0f));
		Scene::Initialize();

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
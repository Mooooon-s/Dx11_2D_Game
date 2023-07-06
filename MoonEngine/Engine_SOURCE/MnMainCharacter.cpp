#include "MnMainCharacter.h"
#include "MnMeshRenderer.h"
#include "MnResources.h"
#include "MnTransform.h"

namespace Mn
{
	MainCharacter::MainCharacter()
		: _Hp(Character::GetHp())
	{
	}
	MainCharacter::~MainCharacter()
	{
	}
	void MainCharacter::Initialize()
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"SpriteMaterial"));
		GetComponent<Transform>()->Position(Vector3(0.0f, 0.0f, 0.0f));
		GameObject::Initialize();
	}
	void MainCharacter::Update()
	{
		GameObject::Update();
	}
	void MainCharacter::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void MainCharacter::Render()
	{
		GameObject::Render();
	}
}
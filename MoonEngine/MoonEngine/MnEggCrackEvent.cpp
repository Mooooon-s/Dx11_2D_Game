#include "MnEggCrackEvent.h"
#include "MnResources.h"
#include "MnEggCrackButton.h"
#include "MnObject.h"

namespace Mn
{
	EggCrackEvent::EggCrackEvent()
	{
	}
	EggCrackEvent::~EggCrackEvent()
	{
	}
	void EggCrackEvent::Initialize()
	{
		SetName(L"EggCrackPanel");
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"EggCrackPanel"));
		Vector2 ratio = mr->GetMaterial()->GetTexture()->CalculateRatio();
		GetComponent<Transform>()->Scale(Vector3(ratio.x * 3.6, ratio.y * 3.6, 1.0f));

		EggCrackButton* ECB = object::Instantiate<EggCrackButton>(Vector3(0.0f, 0.0f, -9.1f), eLayerType::UI);
		ECB->Initialize();
		_EventObject.push_back(ECB);

		GameObject::Initialize();
	}
	void EggCrackEvent::Update()
	{
		GameObject::Update();
	}
	void EggCrackEvent::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void EggCrackEvent::Render()
	{
		GameObject::Render();
	}
	void EggCrackEvent::FontRender()
	{
		GameObject::FontRender();
	}
}
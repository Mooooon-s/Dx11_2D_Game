#include "MnAquarimBG.h"
#include "MnMeshRenderer.h"
#include "MnResources.h"

namespace Mn
{
	AquarimBG::AquarimBG(eAquarim stage)
		: _Stage(stage)
	{
	}
	AquarimBG::~AquarimBG()
	{
	}
	void AquarimBG::Initialize()
	{
		SetName(L"AquarimBG");
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(StageName()));
		Vector2 ratio = mr->GetMaterial()->GetTexture()->CalculateRatio();
		GetComponent<Transform>()->Position(Vector3(0.0f, 0.0f, 2.9f));
		GetComponent<Transform>()->Scale(Vector3(ratio.x * 3.6, ratio.y * 3.6, 1.0f));

	}
	void AquarimBG::Update()
	{
		GameObject::Update();
	}
	void AquarimBG::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void AquarimBG::Render()
	{
		GameObject::Render();
	}
	std::wstring AquarimBG::StageName()
	{
		int level = ((UINT)_Stage+1);
		std::wstring key = L"Stage_";
		std::wstring backKey = std::to_wstring(level)+ L"_background";
		key +=backKey;

		return key;
	}
}

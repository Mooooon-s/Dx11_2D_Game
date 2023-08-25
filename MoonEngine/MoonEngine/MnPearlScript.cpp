#include "MnPearlScript.h"
#include "MnMeshRenderer.h"
#include "MnAnimator.h"
#include "MnTexture.h"
#include "MnGameObject.h"
#include "MnResources.h"
#include "MnTime.h"

namespace Mn
{
	PearlScript::PearlScript()
	{
	}
	PearlScript::~PearlScript()
	{
	}
	void PearlScript::Initialize()
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();
		tr->Scale(Vector3(0.5f, 0.5f, 0.0f));

		MeshRenderer* mr = GetOwner()->AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"PearlSpriteAnimaionMaterial"));


		Animator* at = GetOwner()->AddComponent<Animator>();
		
		std::shared_ptr<Mn::graphics::Texture> atlas 
			= Resources::Load<Mn::graphics::Texture>(L"Pearl", L"..\\Resources\\Texture\\Item\\pearl\\pearl.jpg");
		std::shared_ptr<Mn::graphics::Texture> atlasAlpha 
			= Resources::Load<Mn::graphics::Texture>(L"Pearl_Alpha", L"..\\Resources\\Texture\\Item\\pearl\\pearl_.jpg");

		at->Create(L"Pearl", atlas, atlasAlpha, Vector2::Zero, Vector2(72.0f,72.0f), 2, Vector2::Zero, 1);

		at->PlayAnimation(L"Pearl", true);
	}
	void PearlScript::Update()
	{
		//1.9,1.4
		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector3 pos = tr->Position();
		Vector3 target = Vector3(1.9f, 1.4f, pos.z);
		Vector3 Vec = target - pos;
		Vec.Normalize();
		pos += Vec * 4.0f * Time::DeltaTime();
		tr->Position(pos);
	}
	void PearlScript::LateUpdate()
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector3 pos = tr->Position();
		if (pos.x >= 1.9f && pos.y >= 1.4f)
		{
			GetOwner()->State(GameObject::eState::Dead);
		}
	}
	void PearlScript::Render()
	{
	}
}
#include "MnChomp.h"
#include "MnMeshRenderer.h"
#include "MnResources.h"
#include "MnAnimator.h"

namespace Mn
{
	Chomp::Chomp()
	{
	}
	Chomp::~Chomp()
	{
	}
	void Chomp::Initialize()
	{
		Transform* tr = GetComponent<Transform>();
		tr->Scale(Vector3(0.3f, 0.3f, 0.0f));

		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"SpriteAnimaionMaterial"));
		mr->FlipX(1);

		std::shared_ptr<Mn::graphics::Texture> atlas
			= Resources::Load<Mn::graphics::Texture>(L"Chomp_Sprite", L"..\\Resources\\Texture\\FX\\chomp\\Chomp.jpg");
		std::shared_ptr<Mn::graphics::Texture> atlasAlpha
			= Resources::Load<Mn::graphics::Texture>(L"Chomp_Sprite_Alpha", L"..\\Resources\\Texture\\FX\\chomp\\Chomp_.jpg");

		Animator* at = AddComponent<Animator>();
		at->Create(L"Chomp", atlas, atlasAlpha, Vector2::Zero, Vector2(30.0f, 30.0f), 5, Vector2::Zero, 0.1f);

		at->PlayAnimation(L"Chomp", true);

		GameObject::Initialize();
	}
	void Chomp::Update()
	{
		Animator* at = GetComponent<Animator>();
		if (at->AnimationComplete())
			this->State(GameObject::eState::Dead);
		GameObject::Update();
	}
	void Chomp::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void Chomp::Render()
	{
		GameObject::Render();
	}
}

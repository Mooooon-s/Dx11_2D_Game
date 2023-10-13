#include "MnTailFlop.h"
#include "MnResources.h"
#include "MnAnimator.h"

namespace Mn
{
	TailFlop::TailFlop()
	{
	}
	TailFlop::~TailFlop()
	{
	}
	void TailFlop::Initialize()
	{
		Transform* tr = GetComponent<Transform>();
		tr->Scale(Vector3(1.65f, 0.5f, 0.0f));

		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"SpriteAnimaionMaterial"));
		mr->FlipX(0);

		Animator* at = AddComponent<Animator>();

		std::shared_ptr<Mn::graphics::Texture> atlas
			= Resources::Load<Mn::graphics::Texture>(L"Tail_Sprite", L"..\\Resources\\Texture\\UI\\etc\\tailflop.jpg");
		std::shared_ptr<Mn::graphics::Texture> atlasAlpha
			= Resources::Load<Mn::graphics::Texture>(L"Tail_Sprite_Alpha", L"..\\Resources\\Texture\\UI\\etc\\tailflop_.jpg");

		at->Create(L"Tail_Flop", atlas, atlasAlpha, Vector2::Zero, Vector2(238,165), 10, Vector2::Zero, 1.0f);
		at->PlayAnimation(L"Tail_Flop", true);
	}
	void TailFlop::Update()
	{
		GameObject::Update();
	}
	void TailFlop::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void TailFlop::Render()
	{
		GameObject::Render();
	}
}
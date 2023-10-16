#include "MnSparkRender.h"
#include "MnGameObject.h"
#include "MnAnimator.h"
#include "MnResources.h"

namespace Mn
{
	SparkRender::SparkRender()
	{
	}
	SparkRender::~SparkRender()
	{
	}
	void SparkRender::Initialize()
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();
		tr->Scale(Vector3(0.5f, 0.5f, 0.0f));

		MeshRenderer* mr = GetOwner()->AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"SpriteAnimaionMaterial"));
		mr->FlipX(0);

		std::shared_ptr<Mn::graphics::Texture> atlas
			= Resources::Load<Mn::graphics::Texture>(L"Spark_Sprite", L"..\\Resources\\Texture\\FX\\sparks\\sparks.jpg");
		std::shared_ptr<Mn::graphics::Texture> atlasAlpha
			= Resources::Load<Mn::graphics::Texture>(L"Spark_Sprite_Alpha", L"..\\Resources\\Texture\\FX\\sparks\\sparks.jpg");

		Animator* at = GetOwner()->AddComponent<Animator>();
		at->Create(L"Sparks", atlas, atlasAlpha, Vector2::Zero, Vector2(40.0f, 40.0f), 5, Vector2::Zero, 0.2f);

		at->PlayAnimation(L"Sparks", true);
	}
	void SparkRender::Update()
	{
	}
	void SparkRender::LateUpdate()
	{
	}
	void SparkRender::Render()
	{
	}
}
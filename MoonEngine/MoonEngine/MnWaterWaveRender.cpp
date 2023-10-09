#include "MnWaterWaveRender.h"
#include "MnMeshRenderer.h"
#include "MnAnimator.h"
#include "MnResources.h"
#include "MnGameObject.h"

namespace Mn
{
	WaterWaveRender::WaterWaveRender()
	{
	}
	WaterWaveRender::~WaterWaveRender()
	{
	}
	void WaterWaveRender::Initialize()
	{
		MeshRenderer* mr = GetOwner()->AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"SpriteAnimaionMaterial"));

		GetOwner()->GetComponent<Transform>()->Scale(Vector3(6, 0.1,0.0f));
		GetOwner()->GetComponent<Transform>()->Position(Vector3(0.0f,1.15,-9.0));

		Animator* at = GetOwner()->AddComponent<Animator>();
		std::shared_ptr<Mn::graphics::Texture> atlas
			= Resources::Load<Mn::graphics::Texture>(L"WaterWave_Sprite", L"..\\Resources\\Texture\\FX\\wavecenter.jpg");
		std::shared_ptr<Mn::graphics::Texture> atlasAlpha
			= Resources::Load<Mn::graphics::Texture>(L"WaterWave_Sprite_Alpha", L"..\\Resources\\Texture\\FX\\wavecenter.jpg");

		at->CreateVertical(L"WaveCenter", atlas, atlasAlpha, Vector2::Zero, Vector2(160, 27), 12, Vector2::Zero, 0.1f);

		at->PlayAnimation(L"WaveCenter", true);
	}
	void WaterWaveRender::Update()
	{
	}
	void WaterWaveRender::LateUpdate()
	{
	}
	void WaterWaveRender::Render()
	{
	}
}
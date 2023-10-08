#include "MnWarpHole.h"

#include "MnTexture.h"
#include "MnResources.h"
#include "MnAnimator.h"
#include "MnMeshRenderer.h"
#include "MnMaterial.h"
#include "MnGameObject.h"
#include "MnTime.h"
#include "MnObject.h"

//Boss Type
#include "MnBalrog.h"
#include "MnSylv.h"

namespace Mn
{
	WarpHole::WarpHole()
		: _Flag(true)
		, _Time(0)
		, _Type(eBossType::Barlog)
	{
	}
	WarpHole::~WarpHole()
	{
	}
	void WarpHole::Initialize()
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"SpriteAnimaionMaterial"));
		mr->FlipX(1);

		std::shared_ptr<Mn::graphics::Texture> atlas
			= Resources::Load<Mn::graphics::Texture>(L"Warphole", L"..\\Resources\\Texture\\FX\\warphole\\warphole.jpg");
		std::shared_ptr<Mn::graphics::Texture> atlasAlpha
			= Resources::Load<Mn::graphics::Texture>(L"Warphole_Alpha", L"..\\Resources\\Texture\\FX\\warphole\\_warphole.jpg");

		Animator* at = AddComponent<Animator>();
		at->Create(L"Warphole", atlas, atlasAlpha, Vector2::Zero, Vector2(60, 220), 17, Vector2::Zero, 0.1f);
		at->PlayAnimation(L"Warphole", true);
	}
	void WarpHole::Update()
	{
		Transform* tr = GetComponent<Transform>();
		Vector3 pos = tr->Position();
		pos.z = -1;
		_Time += Time::DeltaTime();

		if (_Time > 0.8 && _Flag)
		{
			SpawnBoss(pos);
			_Flag = false;
		}

		Animator* at = GetComponent<Animator>();
		if (at->AnimationComplete())
			this->State(eState::Dead);

		GameObject::Update();
	}
	void WarpHole::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void WarpHole::Render()
	{
		GameObject::Render();
	}
	void WarpHole::SpawnBoss(Vector3 pos)
	{
		GameObject* boss;
		switch (_Type)
		{
		case Mn::enums::eBossType::Barlog:
			boss = object::Instantiate<Balrog>(pos, eLayerType::Monster);
			boss->Initialize();
			break;
		case Mn::enums::eBossType::Sylv:
			boss = object::Instantiate<Sylv>(pos, eLayerType::Monster);
			boss->Initialize();
			break;
		}
	}
}
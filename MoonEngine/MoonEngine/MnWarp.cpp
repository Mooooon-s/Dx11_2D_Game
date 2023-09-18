#include "MnWarp.h"
#include "MnWarpHole.h"
#include "MnGameObject.h"
#include "MnObject.h"
#include "MnWarpRenderScript.h"

namespace Mn
{
	Warp::Warp()
	{
	}
	Warp::~Warp()
	{
	}
	void Warp::Initialize()
	{
		WarpRenderScript* WRS = AddComponent<WarpRenderScript>();
		WRS->Initialize();
		Transform* tr = GetComponent<Transform>();
		Vector3 pos = tr->Position();
		pos.z += 0.1;
		WarpHole* hole = object::Instantiate<WarpHole>(pos, eLayerType::Effect);
		hole->Initialize();
	}
	void Warp::Update()
	{
		GameObject::Update();
	}
	void Warp::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void Warp::Render()
	{
		GameObject::Render();
	}
}
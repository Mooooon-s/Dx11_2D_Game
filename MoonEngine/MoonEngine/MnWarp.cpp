#include "MnWarp.h"
#include "MnWarpHole.h"
#include "MnGameObject.h"
#include "MnObject.h"
#include "MnWarpRenderScript.h"

namespace Mn
{
	Warp::Warp()
		: _Type(eBossType::Barlog)
	{
	}
	Warp::~Warp()
	{
	}
	void Warp::Initialize()
	{
		WarpRenderScript* WRS = AddComponent<WarpRenderScript>();
		WRS->Initialize();
		Hole();
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
	void Warp::Hole()
	{
		Transform* tr = GetComponent<Transform>();
		Vector3 pos = tr->Position();
		pos.z += 0.1;
		WarpHole* hole = object::Instantiate<WarpHole>(pos, eLayerType::Effect);
		hole->BossType(_Type);
		/*switch (_Type)
		{
		case Mn::enums::eBossType::Barlog:
			break;
		case Mn::enums::eBossType::Sylv:
			hole->BossType(_Type);
			break;
		case Mn::enums::eBossType::End:
			break;
		default:
			break;
		}*/
		hole->Initialize();
	}
}
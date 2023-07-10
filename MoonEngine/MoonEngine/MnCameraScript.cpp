#include "MnCameraScript.h"
#include "MnTransform.h"
#include "MnGameObject.h"
#include "MnTime.h"
#include "MnInput.h"

namespace Mn
{
	CameraScript::CameraScript()
		: _CamTarget(nullptr)
	{
	}
	void CameraScript::Update()
	{
		if (_CamTarget == nullptr)
		{
			//Transform* tr = GetOwner()->GetComponent<Transform>();
			//Vector3 pos = tr->Position();
			//if (Input::GetKey(eKeyCode::W))
			//{
			//	pos.z += 5.0f * Time::DeltaTime();
			//	tr->Position(pos);
			//}
			//else if (Input::GetKey(eKeyCode::S))
			//{
			//	pos.z -= 5.0f * Time::DeltaTime();
			//	tr->Position(pos);
			//}
			//else if (Input::GetKey(eKeyCode::A))
			//{
			//	pos.x -= 5.0f * Time::DeltaTime();
			//	tr->Position(pos);
			//}
			//else if (Input::GetKey(eKeyCode::D))
			//{
			//	pos.x += 5.0f * Time::DeltaTime();
			//	tr->Position(pos);
			//}
			//else if (Input::GetKey(eKeyCode::Q))
			//{
			//	pos.y -= 5.0f * Time::DeltaTime();
			//	tr->Position(pos);
			//}
			//else if (Input::GetKey(eKeyCode::E))
			//{
			//	pos.y += 5.0f * Time::DeltaTime();
			//	tr->Position(pos);
			//}
		}
		else
		{
			Transform* ctr = _CamTarget->GetComponent<Transform>();
			Transform* tr = GetOwner()->GetComponent<Transform>();
			tr->Position(ctr->Position());
		}
	}
}
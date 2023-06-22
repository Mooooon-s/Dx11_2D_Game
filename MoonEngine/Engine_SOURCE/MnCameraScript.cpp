#include "MnCameraScript.h"
#include "MnTransform.h"
#include "MnGameObject.h"
#include "MnTime.h"

namespace Mn
{
	void CameraScript::Update()
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector3 pos = tr->Position();
		pos.x += 1.0f * Time::DeltaTime();
		tr->Position(pos);
	}
}
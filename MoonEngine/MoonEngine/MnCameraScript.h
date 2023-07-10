#pragma once
#include "MnScript.h"
#include "MnGameObject.h"
namespace Mn
{

	class CameraScript : public Script
	{
	private:
		GameObject* _CamTarget;
	public:
		CameraScript();

		virtual void Update() override;

		void SetTarget(GameObject* target) { _CamTarget = target; }
	};

}

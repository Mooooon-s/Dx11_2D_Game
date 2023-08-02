#pragma once
#include "../Engine_SOURCE/MnGameObject.h"
#include "../Engine_SOURCE/MnScript.h"

namespace Mn
{
	class MousePosScript : public Script
	{
	public:
		MousePosScript();
		MousePosScript(GameObject* cam);

		~MousePosScript();

		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render() override;
	public:
		void UICamera(GameObject* uicamera) { _Cam = uicamera; }
	private:
		Vector3  _WinPos;
		GameObject* _Cam;
	};
}

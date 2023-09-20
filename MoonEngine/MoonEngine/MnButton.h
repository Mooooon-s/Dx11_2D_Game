#pragma once
#include "MnGameObject.h"

namespace Mn
{
	class Button : public GameObject
	{
	public:
		Button();
		virtual ~Button();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();
		virtual void FontRender();
		virtual void OnClick();
		virtual void OnClick(Vector3 pos);
		virtual void MouseOn();
	private:

	};
}

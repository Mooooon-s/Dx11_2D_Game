#pragma once
#include "MnButton.h"

namespace Mn
{
	class EggCrackButton : public Button
	{
	public:
		EggCrackButton();
		~EggCrackButton();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();
		virtual void OnClick();
		virtual void OnClick(Vector3 pos);
		virtual void MouseOn();
		virtual void MouseOff();
	private:
	};
}

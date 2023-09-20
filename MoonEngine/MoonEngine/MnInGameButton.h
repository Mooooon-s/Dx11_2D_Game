#pragma once
#include "MnButton.h"

namespace Mn
{
	class InGameButton : public Button
	{
	public:
		InGameButton();
		~InGameButton();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();
		virtual void OnClick();
		virtual void MouseOn();
	};
}
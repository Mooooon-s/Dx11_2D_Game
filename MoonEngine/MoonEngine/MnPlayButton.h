#pragma once
#include "MnButton.h"

namespace Mn
{
	class PlayButton : public Button
	{
	public:
		PlayButton();
		~PlayButton();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();
		virtual void FontRender();
		virtual void OnClick();
		virtual void OnClick(Vector3 pos);
		virtual void MouseOn();
		virtual void MouseOff();
	private:
		class Animator* _Animator;
		wchar_t _szFloat[50];
	};
}

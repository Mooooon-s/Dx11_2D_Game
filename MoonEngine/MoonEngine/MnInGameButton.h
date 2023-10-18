#pragma once
#include "MnButton.h"
#include "MnObject.h"

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
	public:
		void SetIcon(eIcon icon) { _Icon = icon; }
		eIcon GetIcon() { return _Icon; }
	public:
		void Icon(Vector3 pos);
	private:
		eIcon _Icon;
		GameObject* _IconObject;
	};
}
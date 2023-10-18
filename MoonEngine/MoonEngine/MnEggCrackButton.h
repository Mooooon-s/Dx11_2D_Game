#pragma once
#include "MnButton.h"
#include "MnEggCrackEvent.h"
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
	public:
		void ClickEvent();
		void SpawnPet();
	public:
		void SetIcon(eIcon icon) { _Icon = icon; }
		void SetEvent(EggCrackEvent* obj) { _ECE = obj; }
	private:
		eIcon _Icon;
		EggCrackEvent* _ECE;
	};
}

#pragma once
#include "MnGameObject.h"
#include "MnEggCrackEvent.h"

namespace Mn
{
	class EggCrack : public GameObject
	{
	public:
		EggCrack();
		~EggCrack();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();

	public:
		void Afterstep1();
		void Afterstep2();
		void CreateIconSet();
	public:
		void SetIcon(eIcon icon) { _Icon = icon; }
		void SetEvent(EggCrackEvent* obj) { _EggCrackEvent = obj; }
	private:
		eIcon _Icon;
		EggCrackEvent* _EggCrackEvent;
	};
}

#pragma once
#include "MnGameObject.h"

namespace Mn
{
	class EggCrackEvent : public GameObject
	{
	public:
		EggCrackEvent();
		~EggCrackEvent();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();
		virtual void FontRender();
	private:
		std::vector<GameObject*> _EventObject;
	};
}

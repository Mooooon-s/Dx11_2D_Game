#pragma once
#include "MnGameObject.h"

namespace Mn
{
	class StinkyIcon : public GameObject
	{
	public:
		StinkyIcon();
		~StinkyIcon();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();
	private:
	};
}

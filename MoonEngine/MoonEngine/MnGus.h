#pragma once
#include "MnGameObject.h"

namespace Mn
{
	class Gus : public GameObject
	{
	public:
		Gus();
		~Gus();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();
	private:
	};
}

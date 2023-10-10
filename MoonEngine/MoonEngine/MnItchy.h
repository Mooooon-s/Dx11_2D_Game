#pragma once
#include "MnGameObject.h"

namespace Mn
{
	class Itchy : public GameObject
	{
	public:
		Itchy();
		~Itchy();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();
	private:
	};
}

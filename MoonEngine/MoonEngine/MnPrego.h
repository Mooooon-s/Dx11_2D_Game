#pragma once
#include "MnGameObject.h"

namespace Mn
{
	class Prego : public GameObject
	{
	public:
		Prego();
		~Prego();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();
	private:
	};
}

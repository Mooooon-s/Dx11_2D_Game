#pragma once
#include "MnGameObject.h"

namespace Mn
{
	class Layer
	{
	private:
		std::vector<GameObject*> _GameObjects;
	public:
		Layer();
		~Layer();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();
	};

}

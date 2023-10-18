#pragma once
#include "MnGameObject.h"

namespace Mn
{
	class PregoIcon : public GameObject
	{
	public:
		PregoIcon();
		~PregoIcon();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();
	private:
	};
}

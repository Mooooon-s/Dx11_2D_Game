#pragma once
#include "MnGameObject.h"

namespace Mn
{
	class ZorfIcon : public GameObject
	{
	public:
		ZorfIcon();
		~ZorfIcon();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();
	private:
	};
}

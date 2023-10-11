#pragma once
#include "MnGameObject.h"

namespace Mn
{
	class CaniboarIcon : public GameObject
	{
	public:
		CaniboarIcon();
		~CaniboarIcon();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();
	private:

	};
}

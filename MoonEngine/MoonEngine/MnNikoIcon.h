#pragma once
#include "MnGameObject.h"

namespace Mn
{
	class NikoIcon : public GameObject
	{
	public:
		NikoIcon();
		~NikoIcon();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();
	private:

	};
}

#pragma once
#include "MnGameObject.h"

namespace Mn
{
	class AmpIcon : public GameObject
	{
	public:
		AmpIcon();
		~AmpIcon();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();
	private:
	};
}

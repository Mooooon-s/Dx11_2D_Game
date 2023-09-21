#pragma once
#include "MnGameObject.h"

namespace Mn
{
	class ButtonFrame : public GameObject
	{
	public:
		ButtonFrame();
		~ButtonFrame();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();
	private:

	};
}

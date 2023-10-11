#pragma once
#include "MnGameObject.h"
namespace Mn
{
	class UltravoreIcon : public GameObject
	{
	public:
		UltravoreIcon();
		~UltravoreIcon();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();
	private:
	};
}

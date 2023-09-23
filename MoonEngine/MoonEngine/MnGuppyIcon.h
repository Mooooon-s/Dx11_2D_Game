#pragma once
#include "MnGameObject.h"

namespace Mn
{
	class GuppyIcon : public GameObject
	{
	public:
		GuppyIcon();
		~GuppyIcon();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();
	private:
	};
}

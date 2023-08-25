#pragma once
#include "MnGameObject.h"

namespace Mn
{
	class Pearl : public GameObject
	{
	public:
		Pearl();
		~Pearl();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
	private:

	};
}
#pragma once
#include "MnGameObject.h"

namespace Mn
{
	class SparkEffect : public GameObject
	{
	public:
		SparkEffect();
		~SparkEffect();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();
	private:

	};
}

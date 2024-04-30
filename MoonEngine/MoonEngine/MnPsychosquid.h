#pragma once
#include "MnGameObject.h"

namespace Mn
{
	class Psychosquid : public GameObject
	{
	public:
		Psychosquid();
		~Psychosquid();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();
		virtual void OnClick();
		virtual void OnClick(Vector3 pos);
	private:
	};
}

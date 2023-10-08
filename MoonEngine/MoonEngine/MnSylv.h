#pragma once
#include "MnGameObject.h"

namespace Mn
{
	class Sylv : public GameObject
	{
	public:
		Sylv();
		~Sylv();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();

		virtual void OnClick(Vector3 pos);
	private:
	};
}

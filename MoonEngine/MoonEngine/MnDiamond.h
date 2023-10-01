#pragma once
#include "MnGameObject.h"

namespace Mn
{
	class Diamond : public GameObject
	{
	public:
		Diamond();
		~Diamond();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();
		virtual void OnClick(Vector3 pos);

	private:
		UINT  _Price;
	};
}

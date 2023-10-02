#pragma once
#include "MnGameObject.h"

namespace Mn
{
	class Diamond : public GameObject
	{
	public:
		Diamond();
		~Diamond();

		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render() override;
		void OnClick(Vector3 pos) override;
	private:
		UINT  _Price;
	};
}

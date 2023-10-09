#pragma once
#include "MnGameObject.h"

namespace Mn
{
	class Ultravore : public GameObject
	{
	public:
		Ultravore();
		~Ultravore();

		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render() override;
		void OnClick(Vector3 pos) override;
	private:
	};
}

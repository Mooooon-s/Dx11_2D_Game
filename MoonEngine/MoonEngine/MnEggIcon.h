#pragma once
#include "MnGameObject.h"

namespace Mn
{
	class EggIcon : public GameObject
	{
	public:
		EggIcon();
		~EggIcon();

		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render() override;

		void OnClick() override;
	private:
		int _EggLevel;
	};
}

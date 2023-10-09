#pragma once
#include "MnBackGround.h"

namespace Mn
{
	class WaterWave : public BackGround
	{
	public:
		WaterWave();
		~WaterWave();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;
	private:

	};
}

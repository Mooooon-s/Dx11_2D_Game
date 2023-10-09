#pragma once
#include "MnScript.h"

namespace Mn
{
	class WaterWaveRender : public Script
	{
	public:
		WaterWaveRender();
		~WaterWaveRender();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;
	private:

	};
}

#pragma once
#include "MnScript.h"

namespace Mn
{
	class WarpRenderScript : public Script
	{
	public:
		WarpRenderScript();
		~WarpRenderScript();

		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render() override;
	private:

	};
}

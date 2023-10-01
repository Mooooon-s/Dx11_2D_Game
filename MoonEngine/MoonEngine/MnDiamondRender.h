#pragma once
#include "MnScript.h"

namespace Mn
{
	class DiamondRender : public Script
	{
	public:
		DiamondRender();
		~DiamondRender();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;
	private:

	};
}

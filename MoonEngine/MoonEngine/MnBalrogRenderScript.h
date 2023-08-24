#pragma once
#include "MnScript.h"

namespace Mn
{
	class BalrogRenderScript : public Script
	{
	public:
		BalrogRenderScript();
		~BalrogRenderScript();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;
	private:

	};
}
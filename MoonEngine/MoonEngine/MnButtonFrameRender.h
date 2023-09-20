#pragma once
#include "MnScript.h"

namespace Mn
{
	class ButtonFrameRender : Script
	{
	public:
		ButtonFrameRender();
		~ButtonFrameRender();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;
	private:

	};
}

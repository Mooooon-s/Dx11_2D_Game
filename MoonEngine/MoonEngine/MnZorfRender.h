#pragma once
#include "MnScript.h"

namespace Mn
{
	class ZorfRender : public Script
	{
	public:
		ZorfRender();
		~ZorfRender();

		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render() override;
	private:

	};
}

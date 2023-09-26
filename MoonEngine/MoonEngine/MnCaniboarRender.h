#pragma once
#include "MnScript.h"

namespace Mn
{
	class CaniboarRender : public Script
	{
	public:
		CaniboarRender();
		~CaniboarRender();

		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render() override;

		void AfterSwim();
	private:

	};
}

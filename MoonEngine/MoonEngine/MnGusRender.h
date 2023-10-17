#pragma once
#include "MnScript.h"

namespace Mn
{
	class GusRender : public Script
	{
	public:
		GusRender();
		~GusRender();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

	public:
		void afterTurn();
		void afterEat();

	private:
	};
}

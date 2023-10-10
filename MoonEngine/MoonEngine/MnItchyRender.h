#pragma once
#include "MnScript.h"

namespace Mn
{
	class ItchyRender : public Script
	{
	public:
		ItchyRender();
		~ItchyRender();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		void AfterIdleTurn();
		void AfterAttaclTurn();
	private:
	};
}
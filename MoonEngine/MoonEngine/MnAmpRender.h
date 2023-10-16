#pragma once 
#include "MnScript.h"

namespace Mn
{
	class AmpRender : public Script
	{
	public:
		AmpRender();
		~AmpRender();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;
	public:
		void AfterTurn();
		void AfterChargeTurn();
	};
}

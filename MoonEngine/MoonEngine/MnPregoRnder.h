#pragma once
#include "MnScript.h"

namespace Mn
{
	class PregoRnder : public Script
	{
	public:
		PregoRnder();
		~PregoRnder();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

	public:
		void afterAction();
		void afterPreg();
		void PregGuppy();
		void afterPregTurn();
	private:
	};
}

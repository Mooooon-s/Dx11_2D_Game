#pragma once
#include "MnScript.h"

namespace Mn
{

	class StinkyRenderScript : public Script
	{
	public:
		StinkyRenderScript();
		~StinkyRenderScript();

		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render() override;
	public:
		void Direction2Right();
		void Direction2Left();
		void AfterTurn();
	private:
	};

}
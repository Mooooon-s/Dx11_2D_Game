#pragma once
#include "MnScript.h"

namespace Mn
{

	class FoodScript : public Script
	{
	public:
		FoodScript();
		~FoodScript();

		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render() override;
	private:
		float _Speed;
		float _Alpha;
	};

}
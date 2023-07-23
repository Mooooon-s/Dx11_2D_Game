#pragma once
#include "MnScript.h"

namespace Mn
{

	class GuppyAnimationCntrl : public Script
	{
	public:
		GuppyAnimationCntrl();
		~GuppyAnimationCntrl();

		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render() override;
	private:
		bool _Hungry;
		eBehavior _Behavior;
	};

}
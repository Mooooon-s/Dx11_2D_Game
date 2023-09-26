#pragma once
#include "MnFish.h"

namespace Mn
{
	class Caniboar : public Fish
	{
	public:
		Caniboar();
		~Caniboar();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();
	public:
		void SetFishState(eFishState state) { Mn::Fish::SetFishState(state); }
		eFishState GetFishState() { return Mn::Fish::GetFishState(); }
	private:
		int _Flag;
	};
}

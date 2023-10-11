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
		virtual void OnClick();
	public:
		void DropIntoTank();
	public:
		void SetFishState(eFishState state) { Mn::Fish::SetFishState(state); }
		eFishState GetFishState() { return Mn::Fish::GetFishState(); }
		void SetFlag(int flag) { _Flag = flag; }
	private:
		int _Flag;
	};
}

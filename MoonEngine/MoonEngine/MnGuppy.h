#pragma once
#include "MnFish.h"
#include "MnGuppyBehaviorTree.h"

namespace Mn
{

	class Guppy : public Fish
	{
	public:
		Guppy();
		~Guppy();

		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render() override;

		void SetFishState(eFishState state) { Mn::Fish::SetFishState(state); }
		eFishState GetFishState() { return Mn::Fish::GetFishState(); }

		UINT FishLevel();
	private:
		GuppyBehaviorTree* _GBT;
		int _Flag;
	};

}
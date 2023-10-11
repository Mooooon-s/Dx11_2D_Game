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

		void OnClick() override;

		void SetFishState(eFishState state) { Mn::Fish::SetFishState(state); }
		eFishState GetFishState() { return Mn::Fish::GetFishState(); }

		UINT FishLevel();
		bool FishStarving();
		void SetFlag(int flag) { _Flag = flag; }

		void DropIntoTank();
	private:
		GuppyBehaviorTree* _GBT;
		int _Flag;
	};

}
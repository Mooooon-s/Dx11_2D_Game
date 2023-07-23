#pragma once
#include "MnGameObject.h"

namespace Mn
{

	class Fish : public GameObject
	{
	public:
		Fish();
		virtual ~Fish();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		void SetFishState(eFishState fishState) { _FishState = fishState; }
		eFishState GetFishState() { return _FishState; }
	private:
		eFishState _FishState;
	};

}
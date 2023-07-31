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

		void Play();
		void Swim();
		void Turn();
		void HungrySwim();
		void HungryTurn();
	private:
		UINT		_Level;
		bool		_Hungry;
		eBehavior	_Behavior;

		class Animator* _Animator;
	};

}
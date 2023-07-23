#pragma once
#include "MnScript.h"

namespace Mn
{

	class GuppyScript : public Script
	{
	public:
		GuppyScript();
		~GuppyScript();

		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render() override;

	public:
		void Behavior();
		void Think();
		void Swim();
		void Eat();
		void Turn();
		void MoveVec();

		bool IsHungry() { return _Hungry; }
		eBehavior GetBehavior() { return _Behavior; }

	private:
		UINT		_Level;
		float		_Time;
		float		_Speed;
		bool		_Hungry;
		eDir		_Dir;
		Vector3		_Move;
		eBehavior	_Behavior;
	};

}
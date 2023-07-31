#pragma once

#include "MnScript.h"
#include "MnGuppyBehaviorTree.h"

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
		void MoveVec();

		void SetDir(eDir dir) { _Dir = dir; }
		void SetLevel(UINT level) { _Level = level; }
		void IsHungry(bool hungry) { _Hungry = hungry; }
		void SetBehavior(eBehavior behavior) { _Behavior = behavior; }

		eDir GetDir() { return _Dir; }
		UINT GetLevel() { return _Level; }
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
		GuppyBehaviorTree* _Tree;
	};

}
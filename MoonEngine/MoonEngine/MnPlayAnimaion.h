#pragma once
#include "MnBtNode.h"
#include "MnBlackBoard.h"

namespace Mn
{
	class PlayAnimaion : public Node
	{
	public:
		PlayAnimaion();
		PlayAnimaion(BlackBoard* blackboard);
	public:
		virtual enums::eBTState Run()override;
		void PlayAnimation(enums::eBehavior behavior);
		void FullAnimation(enums::eBehavior behavior);
		void DeathAnimation();
		void StarvingAnimation(enums::eBehavior behavior);
		void Bind();
		void afterAction();
	private:
		BlackBoard*		_BlackBoard;
		eBehavior		_Behavior;
		eFishState		_State;
		UINT			_Level;
	};

}
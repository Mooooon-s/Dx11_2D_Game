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
		void StarvingAnimation(enums::eBehavior behavior);
		void Bind();
	private:
		BlackBoard* _BlackBoard;
		eBehavior _Behavior;
	};

}
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
		void FullAnimaton(enums::eBehavior behavior);
	private:
		BlackBoard* _BlackBoard;
		eBehavior _Behavior;
	};

}
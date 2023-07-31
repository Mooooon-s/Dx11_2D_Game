#pragma once
#include "MnBtNode.h"
#include "MnBlackBoard.h"

namespace Mn
{
	class Move : public Node
	{
	public:
		Move();
		Move(BlackBoard* blackboard);
	public:
		virtual enums::eBTState Run();
	private:
		BlackBoard* _Blackboard;
		float _Time;
		float _Speed;
	};

}
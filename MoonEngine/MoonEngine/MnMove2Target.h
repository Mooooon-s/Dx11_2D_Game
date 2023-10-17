#pragma once
#include "MnBtNode.h"
#include "MnBlackBoard.h"

namespace Mn
{
	class Move2Target : public Node
	{
	public:
		Move2Target();
		Move2Target(BlackBoard* board);
		~Move2Target();

		enums::eBTState Run() override;
	public:
		void Move2Food();
		void Move2Fish();
	private:
		BlackBoard* _BlackBoard;
	};
}

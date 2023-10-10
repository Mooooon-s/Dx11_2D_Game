#pragma once
#include "MnBtNode.h"
#include "MnBlackBoard.h"

namespace Mn
{
	class Move2Boss : public Node
	{
	public:
		Move2Boss();
		Move2Boss(BlackBoard* board);
		~Move2Boss();

		enums::eBTState Run() override;
	private:
		BlackBoard* _BlackBoard;
	};
}

#pragma once
#include "MnBlackBoard.h"
#include "MnBtNode.h"

namespace Mn
{
	class Move2Coin : public Node
	{
	public:
		Move2Coin();
		Move2Coin(BlackBoard* board);
		~Move2Coin();

		enums::eBTState Run() override;
	private:
		BlackBoard* _BlackBoard;
	};
}
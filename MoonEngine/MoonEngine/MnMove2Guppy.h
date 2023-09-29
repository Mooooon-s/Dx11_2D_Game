#pragma once
#include "MnBtNode.h"
#include "MnBlackBoard.h"

namespace Mn
{
	class Move2Guppy : public Node
	{
	public:
		Move2Guppy();
		Move2Guppy(BlackBoard* board);
		~Move2Guppy();

		enums::eBTState Run() override;
	private:
		BlackBoard* _BlackBoard;
	};
}

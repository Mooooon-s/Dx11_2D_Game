#pragma once
#include "MnBtNode.h"
#include "MnBlackBoard.h"

namespace Mn
{
	class Move2Caniboar : public Node
	{
	public:
		Move2Caniboar();
		Move2Caniboar(BlackBoard* board);
		~Move2Caniboar();

		enums::eBTState Run() override;
	private:
		BlackBoard* _BlackBoard;
	};
}

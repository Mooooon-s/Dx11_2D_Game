#pragma once
#include "MnBtNode.h"
#include "MnBlackBoard.h"

namespace Mn
{
	class Move2Fish : public Node
	{
	public:
		Move2Fish();
		Move2Fish(BlackBoard* board);
		~Move2Fish();

		enums::eBTState Run() override;
	private:
		int _Count;
		BlackBoard* _BlackBoard;
	};
}

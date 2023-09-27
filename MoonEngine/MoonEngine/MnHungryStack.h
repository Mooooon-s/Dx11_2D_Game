#pragma once
#include "MnBtNode.h"
#include "MnBlackBoard.h"

namespace Mn
{
	class HungryStack : public Node
	{
	public:
		HungryStack();
		HungryStack(BlackBoard* board);
		~HungryStack();

		enums::eBTState Run() override;
	private:
		BlackBoard* _BlackBoard;
	};
}

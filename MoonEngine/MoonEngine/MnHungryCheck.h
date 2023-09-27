#pragma once
#include "MnBtNode.h"
#include "MnBlackBoard.h"

namespace Mn
{
	class HungryCheck : public Node
	{
	public:
		HungryCheck();
		HungryCheck(BlackBoard* board);
		~HungryCheck();

		virtual enums::eBTState Run();
	private:
		BlackBoard* _BlackBoard;
	};
}

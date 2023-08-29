#pragma once
#include "MnBtNode.h"
#include "MnBlackBoard.h"

namespace Mn
{
	class FindFish : public Node
	{
	public:
		FindFish();
		FindFish(BlackBoard* board);
		~FindFish();

		enums::eBTState Run() override;
	private:
		BlackBoard* _BlackBoard;
	};
}

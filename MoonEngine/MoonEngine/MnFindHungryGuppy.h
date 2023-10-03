#pragma once
#include "MnBtNode.h"
#include "MnBlackBoard.h"

namespace Mn
{
	class FindHungryGuppy : public Node
	{
	public:
		FindHungryGuppy();
		FindHungryGuppy(BlackBoard* board);
		~FindHungryGuppy();

		enums::eBTState Run() override;
	private:
		BlackBoard* _BlackBoard;
	};
}

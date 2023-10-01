#pragma once
#include "MnBtNode.h"
#include "MnBlackBoard.h"

namespace Mn
{
	class Turn2Food : public Node
	{
	public:
		Turn2Food();
		Turn2Food(BlackBoard* board);
		~Turn2Food();

		enums::eBTState Run() override;
	private:
		BlackBoard* _BlackBoard;
	};
}

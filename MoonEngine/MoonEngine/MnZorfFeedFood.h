#pragma once
#include "MnBtNode.h"
#include "MnBlackBoard.h"

namespace Mn
{
	class ZorfFeedFood : public Node
	{
	public:
		ZorfFeedFood();
		ZorfFeedFood(BlackBoard* board);
		~ZorfFeedFood();

		enums::eBTState Run() override;
	private:
		BlackBoard* _BlackBoard;
	};
}

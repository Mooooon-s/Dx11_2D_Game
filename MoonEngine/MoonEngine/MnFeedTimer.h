#pragma once
#include "MnBtNode.h"
#include "MnBlackBoard.h"

namespace Mn
{
	class FeedTimer : public Node
	{
	public:
		FeedTimer();
		FeedTimer(BlackBoard* board);
		~FeedTimer();

		enums::eBTState Run() override;
	private:
		BlackBoard* _BlackBoard;
		float _Timer;
	};
}

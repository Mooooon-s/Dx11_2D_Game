#pragma once
#include "MnBtNode.h"
#include "MnBlackBoard.h"

namespace Mn
{
	class ZorfFeedDone : public Node
	{
	public:
		ZorfFeedDone();
		ZorfFeedDone(BlackBoard* board);
		~ZorfFeedDone();

		enums::eBTState Run() override;
	private:
		BlackBoard* _BlackBoard;

	};
}

#pragma once
#include "MnBtNode.h"
#include "MnBlackBoard.h"

namespace Mn
{
	class IsCharged : public Node
	{
	public:
		IsCharged();
		IsCharged(BlackBoard* board);
		~IsCharged();

		enums::eBTState Run();
	private:
		BlackBoard* _Blackboard;
	};
}

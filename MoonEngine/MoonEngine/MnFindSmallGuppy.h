#pragma once
#include "MnBtNode.h"
#include "MnBlackBoard.h"

namespace Mn
{
	class FindSmallGuppy : public Node
	{
	public:
		FindSmallGuppy();
		FindSmallGuppy(BlackBoard* board);
		~FindSmallGuppy();

		enums::eBTState Run() override;
	private:
		BlackBoard* _BlackBoard;
	};
}

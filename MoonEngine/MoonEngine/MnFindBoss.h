#pragma once
#include "MnBtNode.h"
#include "MnBlackBoard.h"

namespace Mn
{
	class FindBoss : public Node
	{
	public:
		FindBoss();
		FindBoss(BlackBoard* board);
		~FindBoss();

		enums::eBTState Run() override;
	private:
		BlackBoard* _BlackBoard;
	};

}
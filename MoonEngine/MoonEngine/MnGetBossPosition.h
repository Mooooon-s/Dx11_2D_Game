#pragma once
#include "MnBtNode.h"
#include "MnBlackBoard.h"

namespace Mn
{
	class GetBossPosition : public Node
	{
	public:
		GetBossPosition();
		GetBossPosition(BlackBoard* board);
		~GetBossPosition();

		enums::eBTState Run() override;
	private:
		BlackBoard* _BlackBoard;
	};
}

#pragma once
#include "MnBtNode.h"
#include "MnBlackBoard.h"

namespace Mn
{
	class DetectBoss : public Node
	{
	public:
		DetectBoss();
		DetectBoss(BlackBoard* board);
		~DetectBoss();

		enums::eBTState Run() override;
	private:
		BlackBoard* _BlackBoard;
	};
}

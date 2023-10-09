#pragma once
#include "MnBtNode.h"
#include "MnBlackBoard.h"

namespace Mn
{
	class DropTresure : public Node
	{
	public:
		DropTresure();
		DropTresure(BlackBoard* board);
		~DropTresure();

		enums::eBTState Run() override;
	private:
		BlackBoard* _BlackBoard;
		float _ZPositon;
	};
}

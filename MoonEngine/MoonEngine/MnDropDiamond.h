#pragma once
#include "MnBtNode.h"
#include "MnBlackBoard.h"

namespace Mn
{
	class DropDiamond : public Node
	{
	public:
		DropDiamond();
		DropDiamond(BlackBoard* board);
		~DropDiamond();

		enums::eBTState Run() override;
	private:
		BlackBoard* _BlackBoard;
		float _ZPositon;
	};
}

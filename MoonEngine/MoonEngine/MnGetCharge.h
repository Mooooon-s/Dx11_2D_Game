#pragma once
#include "MnBtNode.h"
#include "MnBlackBoard.h"

namespace Mn
{
	class GetCharge : public Node
	{
	public:
		GetCharge();
		GetCharge(BlackBoard* board);
		~GetCharge();

		enums::eBTState Run();
	private:
		BlackBoard* _BlackBoard;
	};
}

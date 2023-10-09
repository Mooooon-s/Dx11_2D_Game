#pragma once
#include "MnBtNode.h"
#include "MnBlackBoard.h"

namespace Mn
{
	class FindCaniboar : public Node
	{
	public:
		FindCaniboar();
		FindCaniboar(BlackBoard* board);
		~FindCaniboar();

		enums::eBTState Run() override;
	private:
		BlackBoard* _BlackBoard;
	};
}

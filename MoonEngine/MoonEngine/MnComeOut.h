#pragma once
#include "MnBtNode.h"
#include "MnBlackBoard.h"

namespace Mn
{
	class ComeOut : public Node
	{
	public:
		ComeOut();
		ComeOut(BlackBoard* board);
		~ComeOut();

		virtual enums::eBTState Run() override;
	private:
		BlackBoard* _BlackBoard;
	};
}

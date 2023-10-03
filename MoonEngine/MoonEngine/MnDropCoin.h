#pragma once
#include "../Engine_SOURCE/MnBtNode.h"
#include "../Engine_SOURCE/MnBlackBoard.h"

namespace Mn
{
	class DropCoin : public Node
	{
	public:
		DropCoin();
		DropCoin(BlackBoard* board);
		~DropCoin();

		virtual enums::eBTState Run() override;
	private:
		BlackBoard* _BlackBoard;
		float		_Time;
	};
}

#pragma once
#include "../Engine_SOURCE/MnBtNode.h"
#include "../Engine_SOURCE/MnBlackBoard.h"

namespace Mn
{
	class GuppyDeath : public Node
	{
	public:
		GuppyDeath();
		GuppyDeath(BlackBoard* board);
		~GuppyDeath();

		virtual enums::eBTState Run() override;
	private:
		BlackBoard* _BlackBoard;
	};
}

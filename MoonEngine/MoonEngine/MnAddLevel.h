#pragma once
#include "../Engine_SOURCE/MnBtNode.h"
#include "../Engine_SOURCE/MnBlackBoard.h"

namespace Mn
{
	class AddLevel : public Node
	{
	public:
		AddLevel();
		AddLevel(BlackBoard* board);
		~AddLevel();

		virtual enums::eBTState Run() override;
	private:
		BlackBoard* _BlackBoard;
	};
}

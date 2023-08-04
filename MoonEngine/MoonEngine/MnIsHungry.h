#pragma once
#include "../Engine_SOURCE/MnBtNode.h"
#include "../Engine_SOURCE/MnBlackBoard.h"

namespace Mn
{
	class IsHungry : public Node
	{
	public:
		IsHungry();
		IsHungry(BlackBoard* board);
		~IsHungry();

		virtual enums::eBTState Run();
	public:

	private:
		BlackBoard* _BlackBoard;
	};

}
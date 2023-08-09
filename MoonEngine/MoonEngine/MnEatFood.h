#pragma once
#include "../Engine_SOURCE/MnBtNode.h"
#include "../Engine_SOURCE/MnBlackBoard.h"

namespace Mn
{

	class EatFood : public Node
	{
	public:
		EatFood();
		EatFood(BlackBoard* board);
		~EatFood();

		virtual enums::eBTState Run() override;
	private:
		BlackBoard* _BlackBoard;
	};

}
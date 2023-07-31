#pragma once
#include "../Engine_SOURCE/MnBtNode.h"
#include "../Engine_SOURCE/MnBlackBoard.h"

namespace Mn
{

	class FindFood : public Node
	{
	public:
		FindFood();
		FindFood(BlackBoard* blakcboard);
		~FindFood();
	public:
		virtual enums::eBTState Run() override;
	private:
		BlackBoard* _BlackBoard;

	};

}
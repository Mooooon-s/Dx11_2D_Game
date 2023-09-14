#pragma once
#include "MnBtNode.h"
#include "MnBlackBoard.h"

namespace Mn
{

	class GuppyFoodTurn : public Node
	{
	public:
		GuppyFoodTurn();
		GuppyFoodTurn(BlackBoard* board);
		~GuppyFoodTurn();

		virtual enums::eBTState Run() override;
	private:
		BlackBoard* _BlackBoard;
	};

}
#pragma once
#include "../Engine_SOURCE/MnBtNode.h"
#include "../Engine_SOURCE/MnBlackBoard.h"
namespace Mn
{

	class GuppyTurn : public Node
	{
	public:
		GuppyTurn();
		GuppyTurn(BlackBoard* board);

		virtual enums::eBTState Run() override;

	private:
		BlackBoard* _Blackboard;
	};

}
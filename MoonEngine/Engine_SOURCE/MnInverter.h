#pragma once
#include "MnDecoratorNode.h"
#include "MnBlackBoard.h"

namespace Mn
{
	class Inverter : public DecoratorNode
	{
	public:
		Inverter() : _BlackBoard(nullptr) {}
		Inverter(BlackBoard* blackboard)
			: DecoratorNode(blackboard)
			, _BlackBoard(blackboard)
		{

		}
		virtual enums::eBTState Run() override;
	private:
		BlackBoard* _BlackBoard;
	};

}
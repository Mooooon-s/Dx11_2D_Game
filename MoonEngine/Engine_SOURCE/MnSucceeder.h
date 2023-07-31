#pragma once
#include "MnDecoratorNode.h"

namespace Mn
{
	class Succeeder : public DecoratorNode
	{
	public:
		Succeeder() : _BlackBoard(nullptr) {}
		Succeeder(BlackBoard* blackboard)
			: DecoratorNode(blackboard)
			, _BlackBoard(blackboard)
		{

		}
		virtual enums::eBTState Run() override;
	private:
		BlackBoard* _BlackBoard;
	};
}

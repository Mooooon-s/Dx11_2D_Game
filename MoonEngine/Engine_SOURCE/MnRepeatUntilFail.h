#pragma once
#include "MnDecoratorNode.h"

namespace Mn
{
	class RepeatUntilFail : public DecoratorNode
	{
	public:
		RepeatUntilFail() :_BlackBoard(nullptr) {}
		RepeatUntilFail(BlackBoard* blackboard)
			:_BlackBoard(blackboard)
		{

		}
		virtual enums::eBTState Run() override;
	private:
		BlackBoard* _BlackBoard;
	};
}
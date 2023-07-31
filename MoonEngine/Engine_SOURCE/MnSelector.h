#pragma once
#include "MnCompositeNode.h"
#include "MnBlackBoard.h"

namespace Mn
{
	class Selector : public CompositeNode
	{
	public:
		Selector();
		Selector(BlackBoard* blackboard);
		virtual enums::eBTState Run() override;
	private:
		BlackBoard* _BlackBoard;
	};
}

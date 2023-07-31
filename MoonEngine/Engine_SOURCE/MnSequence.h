#pragma once
#include "MnCompositeNode.h"

namespace Mn
{
	class Sequence : public CompositeNode
	{
	public:
		Sequence();
		Sequence(BlackBoard* blackboard);
		virtual enums::eBTState Run() override;
	private:
		BlackBoard* _BlackBoard;
	};
}
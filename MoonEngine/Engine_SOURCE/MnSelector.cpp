#include "MnSelector.h"
namespace Mn
{
	Selector::Selector()
		:CompositeNode()
		, _BlackBoard(nullptr)
	{
	}
	Selector::Selector(BlackBoard* blackboard)
		:CompositeNode(blackboard)
		,_BlackBoard(blackboard)
	{
	}
	enums::eBTState Selector::Run()
	{
		for (Node* child : GetChildren())
		{
			enums::eBTState state = child->Run();

			if (state == enums::eBTState::RUNNING)
				return enums::eBTState::RUNNING;

			if (state == enums::eBTState::SUCCESS)
				return enums::eBTState::SUCCESS;
		}
		return enums::eBTState::FAILURE;
	}
}
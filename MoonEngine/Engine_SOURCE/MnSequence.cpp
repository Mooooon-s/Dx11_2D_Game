#include "MnSequence.h"
namespace Mn
{
	Sequence::Sequence()
		:CompositeNode()
		,_BlackBoard(nullptr)
	{
	}
	Sequence::Sequence(BlackBoard* blackboard)
		: CompositeNode(blackboard)
		, _BlackBoard(blackboard)
	{
	}
	enums::eBTState Sequence::Run()
	{
		for (Node* child : GetChildren())
		{
			enums::eBTState state = child->Run();
			
			if (state == enums::eBTState::RUNNING)
				return enums::eBTState::RUNNING;

			if (state == enums::eBTState::FAILURE)
				return enums::eBTState::FAILURE;
		}
		return enums::eBTState::SUCCESS;
	}
}
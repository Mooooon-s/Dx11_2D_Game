#include "MnRootNode.h"
#include "MnMove.h"
#include "MnPlayAnimaion.h"

namespace Mn
{
	enums::eBTState RootNode::Run()
	{
		if (CheckRunning() == false)
		{
			return _RunningNode->Run();
		}
		enums::eBTState state = _Child->Run();
		if (state == enums::eBTState::RUNNING)
			_RunningNode = *_BlackBoard->GetRunningNode();
		return state;
	}
	bool RootNode::CheckRunning()
	{
		if (_BlackBoard->GetRunningNode() != nullptr)
			return false;
		return true;
	}
}
#include "MnRootNode.h"
#include "MnMove.h"
#include "MnPlayAnimaion.h"
#include "MnTime.h"

namespace Mn
{
	enums::eBTState RootNode::Run()
	{
		_Time = _BlackBoard->GetDataValue<float>(L"Timer");
		_Time += Time::DeltaTime();
		_BlackBoard->SetData(L"Timer", _Time);

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
	void RootNode::SetTimer()
	{
		_BlackBoard->MakeData<float>(L"Timer");
		_BlackBoard->SetData(L"Timer", _Time);
	}
}
#include "MnRootNode.h"
#include "MnMove.h"
#include "MnPlayAnimaion.h"
#include "MnTime.h"
#include "MnGameObject.h"

namespace Mn
{
	enums::eBTState RootNode::Run()
	{
		if (_BlackBoard->GetData<GameObject>(L"Owner")->State() == Mn::GameObject::eState::Dead) return eBTState::FAILURE;
		_Time = _BlackBoard->GetDataValue<float>(L"Timer");
		_Time += Time::DeltaTime();
		_BlackBoard->SetData(L"Timer", _Time);

		if (CheckRunning() == false)
		{
			enums::eBTState state = _RunningNode->Run();
			if ( state == enums::eBTState::FAILURE || state == enums::eBTState::SUCCESS)
			{
				_BlackBoard->ResetRunningNode();
			}
			return state;
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
#include "MnZorfFeedFood.h"
#include "MnFood.h"
#include "MnObject.h"
#include "MnGameObject.h"
#include "MnZorfAnimationCntrl.h"

namespace Mn
{
	ZorfFeedFood::ZorfFeedFood()
		: _BlackBoard(nullptr)
	{
	}
	ZorfFeedFood::ZorfFeedFood(BlackBoard* board)
		: _BlackBoard(board)
	{
	}
	ZorfFeedFood::~ZorfFeedFood()
	{
	}
	enums::eBTState ZorfFeedFood::Run()
	{
		if (_BlackBoard->GetDataValue<bool>(L"FeedReady"))
		{
			_BlackBoard->SetData(L"Behavior", eBehavior::Feed);
			_BlackBoard->GetData<ZorfAnimationCntrl>(L"AnimaCntrl")->Run();
			_BlackBoard->SetData(L"FeedReady", false);
			return enums::eBTState::SUCCESS;
		}
		return enums::eBTState::SUCCESS;
	}
}
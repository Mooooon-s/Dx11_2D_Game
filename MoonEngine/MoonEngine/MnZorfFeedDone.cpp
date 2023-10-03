#include "MnZorfFeedDone.h"
#include "MnGameObject.h"
#include "MnAnimator.h"
#include "MnZorfAnimationCntrl.h"
#include "MnFood.h"
#include "MnObject.h"

namespace Mn
{
	ZorfFeedDone::ZorfFeedDone()
		: _BlackBoard(nullptr)
	{
	}
	ZorfFeedDone::ZorfFeedDone(BlackBoard* board)
		: _BlackBoard(board)
	{
	}
	ZorfFeedDone::~ZorfFeedDone()
	{
	}
	enums::eBTState ZorfFeedDone::Run()
	{
		GameObject* owner = _BlackBoard->GetData<GameObject>(L"Owner");
		Animator* at = owner->GetComponent<Animator>();
		if (at->AnimationComplete())
		{
			_BlackBoard->SetData(L"Behavior", eBehavior::Swim);
			_BlackBoard->GetData<ZorfAnimationCntrl>(L"AnimaCntrl")->Run();
			GameObject* owner = _BlackBoard->GetData<GameObject>(L"Owner");
			Transform* tr = owner->GetComponent<Transform>();
			Vector3 pos = tr->Position();
			pos.z -= 0.00001f;
			Food* food = object::Instantiate<Food>(pos, eLayerType::Food);
			food->FoodLevel(2);
			food->Initialize();
			return enums::eBTState::SUCCESS;
		}
		else
		{
			_BlackBoard->SetRunningNode<ZorfFeedDone>(this);
			return enums::eBTState::RUNNING;
		}
	}
}
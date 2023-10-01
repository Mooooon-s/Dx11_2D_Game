#include "MnFindSmallGuppy.h"
#include "MnSceneManager.h"
#include "MnGuppy.h"

#include "MnAnimator.h"
#include "MnCaniBoarAnimatonCntrl.h"

namespace Mn
{
	FindSmallGuppy::FindSmallGuppy()
		: _BlackBoard(nullptr)
	{
	}
	FindSmallGuppy::FindSmallGuppy(BlackBoard* board)
		: _BlackBoard(board)
	{
	}
	FindSmallGuppy::~FindSmallGuppy()
	{
	}
	enums::eBTState FindSmallGuppy::Run()
	{
		eFishState state = _BlackBoard->GetDataValue<eFishState>(L"Fish_State");

		if(state == eFishState::Full)
			return enums::eBTState::FAILURE;

		Scene* scene =SceneManager::ActiveScene();

		GameObject* owner = _BlackBoard->GetData<GameObject>(L"Owner");

		Animator* at = owner->GetComponent<Animator>();
		eBehavior behavior = _BlackBoard->GetDataValue<eBehavior>(L"Behavior");
		
		if (at->AnimationComplete() && behavior == eBehavior::Turn)
		{
			eDir dir = _BlackBoard->GetDataValue<eDir>(L"Dir");

			_BlackBoard->SetData(L"Behavior", eBehavior::Swim);
			_BlackBoard->GetData<CaniBoarAnimatonCntrl>(L"AnimaCntrl")->Run();
		}

		std::vector<GameObject*> fish = scene->GetLayer(eLayerType::Fish).GetGameObjects();
		for (auto f : fish)
		{
			if (dynamic_cast<Guppy*>(f))
			{
				Guppy* g = dynamic_cast<Guppy*>(f);
				if (g->FishLevel() == 1)
				{
					Transform* tr = owner->GetComponent<Transform>();
					Vector3 pos = tr->Position();
					Transform* gtr = g->GetComponent<Transform>();
					Vector3 gPos = gtr->Position();

					Vector3 MoveVec = gPos - pos;
					_BlackBoard->SetData(L"MoveVector", MoveVec);
					return enums::eBTState::SUCCESS;
				}
			}
		}
		return enums::eBTState::FAILURE;
	}
}
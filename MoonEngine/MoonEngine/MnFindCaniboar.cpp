#include "MnFindCaniboar.h"
#include "MnGameObject.h"
#include "MnCaniboar.h"
#include "MnAnimator.h"
#include "MnMeshRenderer.h"
#include "MnSceneManager.h"
#include "MnUltravoreAnimationCntrl.h"


namespace Mn
{
	FindCaniboar::FindCaniboar()
		: _BlackBoard(nullptr)
	{
	}
	FindCaniboar::FindCaniboar(BlackBoard* board)
		: _BlackBoard(board)
	{
	}
	FindCaniboar::~FindCaniboar()
	{
	}
	enums::eBTState FindCaniboar::Run()
	{
		eFishState state = _BlackBoard->GetDataValue<eFishState>(L"Fish_State");

		if (state == eFishState::Full)
			return enums::eBTState::FAILURE;

		Scene* scene = SceneManager::ActiveScene();
		GameObject* owner = _BlackBoard->GetData<GameObject>(L"Owner");

		Animator* at = owner->GetComponent<Animator>();
		eBehavior behavior = _BlackBoard->GetDataValue<eBehavior>(L"Behavior");

		if (at->AnimationComplete() && behavior == eBehavior::Turn)
		{
			eDir dir = _BlackBoard->GetDataValue<eDir>(L"Dir");

			_BlackBoard->SetData(L"Behavior", eBehavior::Swim);
			_BlackBoard->GetData<UltravoreAnimationCntrl>(L"AnimaCntrl")->Run();
		}

		std::vector<GameObject*> fishobj = scene->GetLayer(eLayerType::Fish).GetGameObjects();
		for (auto f : fishobj)
		{
			if (dynamic_cast<Caniboar*>(f))
			{
				Transform* tr = owner->GetComponent<Transform>();
				Vector3 pos = tr->Position();
				Transform* gtr = f->GetComponent<Transform>();
				Vector3 gPos = gtr->Position();

				Vector3 MoveVec = gPos - pos;
				_BlackBoard->SetData(L"MoveVector", MoveVec);
				return enums::eBTState::SUCCESS;
			}
		}
		return enums::eBTState::FAILURE;
	}
}
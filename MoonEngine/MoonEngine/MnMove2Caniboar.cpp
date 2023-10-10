#include "MnMove2Caniboar.h"
#include "MnGameObject.h"
#include "MnTime.h"
#include "MnAnimator.h"
#include "MnSceneManager.h"
#include "MnUltravoreAnimationCntrl.h"
#include "MnFindCaniboar.h"

namespace Mn
{
	Move2Caniboar::Move2Caniboar()
		: _BlackBoard(nullptr)
	{
	}
	Move2Caniboar::Move2Caniboar(BlackBoard* board)
		: _BlackBoard(board)
	{
	}
	Move2Caniboar::~Move2Caniboar()
	{
	}
	enums::eBTState Move2Caniboar::Run()
	{
		eFishState state = _BlackBoard->GetDataValue<eFishState>(L"Fish_State");
		GameObject* owner = _BlackBoard->GetData<GameObject>(L"Owner");

		Animator* at = owner->GetComponent<Animator>();
		eBehavior behavior = _BlackBoard->GetDataValue<eBehavior>(L"Behavior");

		if (at->AnimationComplete())
		{
			_BlackBoard->SetData(L"Behavior", eBehavior::Swim);
			_BlackBoard->GetData<UltravoreAnimationCntrl>(L"AnimaCntrl")->Run();
		}

		if (state == eFishState::Full)
			return enums::eBTState::FAILURE;

		at->ActiveAnimationPlaySpeed(3.0f);
		Scene* scene = SceneManager::ActiveScene();
		Transform* tr = owner->GetComponent<Transform>();
		Vector3 pos = tr->Position();
		Vector3 moveVec = _BlackBoard->GetDataValue<Vector3>(L"MoveVector");
		moveVec.z = 0;
		moveVec.Normalize();
		pos += Vector3(moveVec.x, moveVec.y, 0.0f) * 2 * Time::DeltaTime();
		tr->Position(pos);

		if (state != eFishState::Full)
		{
			_BlackBoard->SetRunningNode<FindCaniboar>(_BlackBoard->GetData<FindCaniboar>(L"FindCaniboarNode"));
			return enums::eBTState::RUNNING;
		}
		else
		{
			return enums::eBTState::FAILURE;
		}
	}
}
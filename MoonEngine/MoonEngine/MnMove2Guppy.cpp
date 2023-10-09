#include "MnMove2Guppy.h"
#include "MnSceneManager.h"
#include "MnGameObject.h"
#include "MnTime.h"
#include "MnFindSmallGuppy.h"
#include "MnAnimator.h"
#include "MnCaniBoarAnimatonCntrl.h"

namespace Mn
{
	Move2Guppy::Move2Guppy()
		: _BlackBoard(nullptr)
	{
	}
	Move2Guppy::Move2Guppy(BlackBoard* board)
		: _BlackBoard(board)
	{
	}
	Move2Guppy::~Move2Guppy()
	{
	}
	enums::eBTState Move2Guppy::Run()
	{
		eFishState state = _BlackBoard->GetDataValue<eFishState>(L"Fish_State");
		GameObject* owner = _BlackBoard->GetData<GameObject>(L"Owner");


		Animator* at = owner->GetComponent<Animator>();
		eBehavior behavior = _BlackBoard->GetDataValue<eBehavior>(L"Behavior");

		if (at->AnimationComplete())
		{

			_BlackBoard->SetData(L"Behavior", eBehavior::Swim);
			_BlackBoard->GetData<CaniBoarAnimatonCntrl>(L"AnimaCntrl")->Run();
		}

		if (state == eFishState::Full)
			return enums::eBTState::FAILURE;

		Scene* scene = SceneManager::ActiveScene();

		at->ActiveAnimationPlaySpeed(3);
		Transform* tr = owner->GetComponent<Transform>();
		Vector3 pos = tr->Position();
		Vector3 moveVec = _BlackBoard->GetDataValue<Vector3>(L"MoveVector");
		moveVec.z = 0;
		moveVec.Normalize();
		pos += Vector3(moveVec.x, moveVec.y, 0.0f) * 2 * Time::DeltaTime();
		tr->Position(pos);

		if (state != eFishState::Full)
		{
			_BlackBoard->SetRunningNode<FindSmallGuppy>(_BlackBoard->GetData<FindSmallGuppy>(L"FindGuppyNode"));
			return enums::eBTState::RUNNING;
		}
		else
		{
			return enums::eBTState::FAILURE;
		}
	}
}
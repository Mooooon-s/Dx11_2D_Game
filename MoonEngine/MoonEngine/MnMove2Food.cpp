#include "MnMove2Food.h"
#include "../Engine_SOURCE/MnKdTree.h"

#include "MnGameObject.h"
#include "MnTransform.h"
#include "playScene.h"

#include "MnAnimator.h"

#include "MnConstantBuffer.h"
#include "MnRenderer.h"
#include "MnTime.h"
#include "MnPlayAnimaion.h"

#include "MnGuppyFoodTurn.h"

namespace Mn
{
	Move2Food::Move2Food()
		: _BlackBoard(nullptr)
		, _Dir(enums::eDir::Right)
		, _Flag(0)
	{
	}
	Move2Food::Move2Food(BlackBoard* board)
		:_BlackBoard(board)
		, _Dir(enums::eDir::Right)
		, _Flag(0)
	{
	}
	Move2Food::~Move2Food()
	{
	}
	enums::eBTState Move2Food::Run()
	{
		GameObject* owner = _BlackBoard->GetData<GameObject>(L"Owner");
		Transform* tr = owner->GetComponent<Transform>();
		Vector3 ownerPos = tr->Position();
		KdTree* kd = Mn::kdTree;

		eFishState hungrystate = _BlackBoard->GetDataValue<eFishState>(L"Fish_State");

		GameObject* food = kd->Query(owner, 5.0f, 0);
		if (food == nullptr)
			return enums::eBTState::FAILURE;

		Transform* foodTr = food->GetComponent<Transform>();
		Vector3 foodPos = foodTr->Position();

		
		Animator* at = owner->GetComponent<Animator>();
		if (at->AnimationComplete())
		{
			_BlackBoard->SetData(L"Behavior", enums::eBehavior::Swim);
			_BlackBoard->GetData<PlayAnimaion>(L"AnimationPlay")->Run();
		}
	

		at->ActiveAnimationPlaySpeed(3.0f);
		Vector3 moveVec = foodPos - ownerPos;
		moveVec.z = 0.0f;
		moveVec.Normalize();
		float speed = _BlackBoard->GetDataValue<float>(L"MoveSpeed");
		ownerPos += Vector3(moveVec.x, moveVec.y,0.0f)* 2 * Time::DeltaTime();
		tr->Position(ownerPos);

		if (hungrystate != eFishState::Full)
		{
			_BlackBoard->SetRunningNode(_BlackBoard->GetData<GuppyFoodTurn>(L"FoodTurnNode"));
			return enums::eBTState::RUNNING;
		}
		else
		{
			return enums::eBTState::SUCCESS;
		}
	}
}
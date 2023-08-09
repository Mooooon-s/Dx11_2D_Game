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

namespace Mn
{
	Move2Food::Move2Food()
		: _BlackBoard(nullptr)
		, _Dir(enums::eDir::Right)
	{
	}
	Move2Food::Move2Food(BlackBoard* board)
		:_BlackBoard(board)
		, _Dir(enums::eDir::Right)
	{
	}
	Move2Food::~Move2Food()
	{
	}
	enums::eBTState Move2Food::Run()
	{
		//위치 확인
		GameObject* guppy = _BlackBoard->GetData<GameObject>(L"Guppy");
		Transform* guppyTr = guppy->GetComponent<Transform>();
		Vector3 guppyPos = guppyTr->Position();

		KdTree* kd = Mn::kdTree;

		GameObject* food = kd->Query(guppy, 2.0f, 0);
		if (food == nullptr)
			return enums::eBTState::FAILURE;

		Transform* foodTr = food->GetComponent<Transform>();
		Vector3 foodPos = foodTr->Position();

		//좌우 확인
		if (foodPos.x - guppyPos.x < 0)
		{
			//Food is Left
			_Dir = enums::eDir::Left;
		}
		else
		{
			//Food is right
			_Dir = enums::eDir::Right;
		}

		//방향 전환
		
		PlayAnimaion* anima = new PlayAnimaion(_BlackBoard);

		//turn에서 하면되나? 보류
		enums::eDir dir = _BlackBoard->GetDataValue<enums::eDir>(L"Dir");
		if (dir == enums::eDir::Right && _Dir == enums::eDir::Left)
		{
			_BlackBoard->SetData(L"Behavior", enums::eBehavior::Turn);
			anima->Run();
			_BlackBoard->SetData(L"Dir", enums::eDir::Left);
		}
		else if (dir == enums::eDir::Left && _Dir == enums::eDir::Right)
		{
			_BlackBoard->SetData(L"Behavior", enums::eBehavior::Turn);
			anima->Run();
			_BlackBoard->SetData(L"Dir", enums::eDir::Right);
		}

		Animator* at = guppy->GetComponent<Animator>();
		if (at->AnimationComplete())
		{
			_BlackBoard->SetData(L"Behavior", enums::eBehavior::Swim);
			anima->Run();
		}


		//이동하기
		Vector3 moveVec = foodPos - guppyPos;
		moveVec.z = 0.0f;
		moveVec.Normalize();
		float speed = _BlackBoard->GetDataValue<float>(L"MoveSpeed");
		guppyPos += Vector3(moveVec.x, moveVec.y,0.0f)* speed * Time::DeltaTime();
		guppyTr->Position(guppyPos);
		
		if (_BlackBoard->GetDataValue<bool>(L"CollisionEnter") == true || _BlackBoard->GetDataValue<bool>(L"CollisionStay") == true)
		{
			return enums::eBTState::SUCCESS;
		}

		if (guppyPos.x >= foodPos.x + 0.05 || guppyPos.x <= foodPos.x - 0.05
			|| guppyPos.y >= foodPos.y + 0.05 || guppyPos.y <= foodPos.y - 0.05)
		{
			_BlackBoard->SetRunningNode(this);
			return enums::eBTState::RUNNING;
		}

	}
}
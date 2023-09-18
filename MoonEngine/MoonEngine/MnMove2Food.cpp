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
		GameObject* owner = _BlackBoard->GetData<GameObject>(L"Owner");
		Transform* tr = owner->GetComponent<Transform>();
		Vector3 ownerPos = tr->Position();
		KdTree* kd = Mn::kdTree;

		eFishState hungrystate = _BlackBoard->GetDataValue<eFishState>(L"Fish_State");
		if (hungrystate == eFishState::Full)
			return enums::eBTState::SUCCESS;


		GameObject* food = kd->Query(owner, 2.0f, 0);
		if (food == nullptr)
			return enums::eBTState::FAILURE;

		Transform* foodTr = food->GetComponent<Transform>();
		Vector3 foodPos = foodTr->Position();

		PlayAnimaion* anima = new PlayAnimaion(_BlackBoard);
		Animator* at = owner->GetComponent<Animator>();
		if (at->AnimationComplete())
		{
			_BlackBoard->SetData(L"Behavior", enums::eBehavior::Swim);
			anima->Run();
		}
	
		Vector3 moveVec = foodPos - ownerPos;
		moveVec.z = 0.0f;
		moveVec.Normalize();
		float speed = _BlackBoard->GetDataValue<float>(L"MoveSpeed");
		ownerPos += Vector3(moveVec.x, moveVec.y,0.0f)* speed * Time::DeltaTime();
		tr->Position(ownerPos);

		if (ownerPos.x >= foodPos.x + 0.05 || ownerPos.x <= foodPos.x - 0.05
			|| ownerPos.y >= foodPos.y + 0.05 || ownerPos.y <= foodPos.y - 0.05)
		{
			_BlackBoard->SetRunningNode(this);
			return enums::eBTState::RUNNING;
		}

		return enums::eBTState::SUCCESS;
	}
}
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
		GameObject* owner = _BlackBoard->GetData<GameObject>(L"Owner");
		Transform* tr = owner->GetComponent<Transform>();
		Vector3 ownerPos = tr->Position();

		//Find food에서 찾은 먹이의 위치를 계속해서 받아오는게 맞을듯

		//KdTree* kd = Mn::kdTree;

		//GameObject* food = kd->Query(owner, 2.0f, 0);
		//if (food == nullptr)
		//	return enums::eBTState::FAILURE;

		//Transform* foodTr = food->GetComponent<Transform>();
		Vector3 foodPos = _BlackBoard->GetDataValue<Vector3>(L"Food_Pos");

		//좌우 확인 물고기 기준으로 먹이가 어디에 있는지
		if (foodPos.x - ownerPos.x < 0)
			_Dir = enums::eDir::Left;
		else
			_Dir = enums::eDir::Right;

		//방향 전환
		//PlayAnimaion* anima = new PlayAnimaion(_BlackBoard);

		//turn에서 하면되나? 보류
		//애니메이션을 노드로 사용하는것이 아니라 객채로 사용한다면??
		//방향 전환을 재사용성을 고려해서 작성
		//여기서 하는게 맞음?
		//방향 전환은 따로 하는 걸로
		
		
		
		//enums::eDir dir = _BlackBoard->GetDataValue<enums::eDir>(L"Dir");
		//if (dir == enums::eDir::Right && _Dir == enums::eDir::Left)
		//{
		//	_BlackBoard->SetData(L"Behavior", enums::eBehavior::Turn);
		//	anima->Run();
		//	_BlackBoard->SetData(L"Dir", enums::eDir::Left);
		//}
		//else if (dir == enums::eDir::Left && _Dir == enums::eDir::Right)
		//{
		//	_BlackBoard->SetData(L"Behavior", enums::eBehavior::Turn);
		//	anima->Run();
		//	_BlackBoard->SetData(L"Dir", enums::eDir::Right);
		//}

		//Animator* at = owner->GetComponent<Animator>();
		//if (at->AnimationComplete())
		//{
		//	_BlackBoard->SetData(L"Behavior", enums::eBehavior::Swim);
		//	anima->Run();
		//}

		
		//이동하기
		//에니메이션은 최대한 배제하는걸로
		Vector3 moveVec = foodPos - ownerPos;
		moveVec.z = 0.0f;
		moveVec.Normalize();
		float speed = _BlackBoard->GetDataValue<float>(L"MoveSpeed");
		ownerPos += Vector3(moveVec.x, moveVec.y,0.0f)* speed * Time::DeltaTime();
		tr->Position(ownerPos);

		//if (ownerPos.x >= foodPos.x + 0.05 || ownerPos.x <= foodPos.x - 0.05
		//	|| ownerPos.y >= foodPos.y + 0.05 || ownerPos.y <= foodPos.y - 0.05)
		//{
		//	_BlackBoard->SetRunningNode(this);
		//	return enums::eBTState::RUNNING;
		//}

		return enums::eBTState::SUCCESS;
	}
}
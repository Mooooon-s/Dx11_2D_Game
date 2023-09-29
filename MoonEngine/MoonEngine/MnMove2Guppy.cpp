#include "MnMove2Guppy.h"
#include "MnSceneManager.h"
#include "MnGameObject.h"
#include "MnTime.h"
#include "MnFindSmallGuppy.h"

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

		if (state == eFishState::Full)
			return enums::eBTState::FAILURE;

		Scene* scene = SceneManager::ActiveScene();

		GameObject* owner = _BlackBoard->GetData<GameObject>(L"Owner");

		Transform* tr = owner->GetComponent<Transform>();
		Vector3 pos = tr->Position();
		Vector3 moveVec = _BlackBoard->GetDataValue<Vector3>(L"MoveVector");
		moveVec.Normalize();
		float speed = _BlackBoard->GetDataValue<float>(L"MoveSpeed");
		pos += moveVec * speed * Time::DeltaTime();
		tr->Position(pos);

		if (state != eFishState::Full)
		{
			_BlackBoard->SetData(L"StackFlag", 0);
			_BlackBoard->SetRunningNode<FindSmallGuppy>(_BlackBoard->GetData<FindSmallGuppy>(L"FindGuppyNode"));
			return enums::eBTState::RUNNING;
		}
		else
		{
			_BlackBoard->SetData(L"StackFlag", 1);
			return enums::eBTState::FAILURE;
		}
	}
}
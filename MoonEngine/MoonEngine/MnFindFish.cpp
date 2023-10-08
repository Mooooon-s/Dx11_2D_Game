#include "MnFindFish.h"
#include "MnSceneManager.h"
#include "MnGuppy.h"
#include "PLAYSCENE.H"

namespace Mn
{
	FindFish::FindFish()
		: _BlackBoard(nullptr)
	{
	}
	FindFish::FindFish(BlackBoard* board)
		: _BlackBoard(board)
	{
	}
	FindFish::~FindFish()
	{
	}
	enums::eBTState FindFish::Run()
	{
		GameObject* boss = _BlackBoard->GetData<GameObject>(L"Owner");

		GameObject* fish = Mn::GuppyTree->Query(boss,5,0);

		if (fish != nullptr)
		{
			Transform* tr = fish->GetComponent<Transform>();
			Vector3 pos = tr->Position();
			pos.z = 0;
			_BlackBoard->SetData<Vector3>(L"Target_Pos", pos);
		}
		else
		{
			Transform* tr = boss->GetComponent<Transform>();
			Vector3 pos = tr->Position();
			_BlackBoard->SetData<Vector3>(L"Target_Pos", pos);
		}

		if (fish != nullptr)
			return enums::eBTState::SUCCESS;
		else
			return enums::eBTState::SUCCESS;
	}
}
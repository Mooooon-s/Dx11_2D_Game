#include "MnFindFood.h"
#include "MnGameObject.h"
#include "MnKdTree.h"
#include "MnSceneManager.h"
#include "playScene.h"

namespace Mn
{
	FindFood::FindFood()
		:_BlackBoard(nullptr)
	{
	}
	FindFood::FindFood(BlackBoard* blakcboard)
		:_BlackBoard(blakcboard)
	{
	}
	FindFood::~FindFood()
	{
	}
	enums::eBTState FindFood::Run()
	{
		if (_BlackBoard->GetData<KdTree>(L"Food_Tree") != nullptr)
		{
			if(Food()==true)
				return enums::eBTState::SUCCESS;
		}
		return enums::eBTState::FAILURE;
	}
	bool FindFood::Food()
	{
		GameObject* owner = _BlackBoard->GetData<GameObject>(L"Owner");

		KdTree* kd = Mn::kdTree;
		GameObject* food_ = kd->Query(owner, 2.0f,0);
		Transform* ownerTr = owner->GetComponent<Transform>();
		if (food_ != nullptr)
		{
			Transform* foodtr = food_->GetComponent<Transform>();
			_BlackBoard->SetData<Vector3>(L"Food_Pos", foodtr->Position());
			return true;
		}
		else
		{
			_BlackBoard->SetData<Vector3>(L"Food_Pos", ownerTr->Position());
			return false;
		}
	}
}
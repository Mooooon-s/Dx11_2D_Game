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
		GameObject* guppy = _BlackBoard->GetData<GameObject>(L"Guppy");

		KdTree* kd = Mn::kdTree;
		GameObject* food_ = kd->Query(guppy, 2.0f,0);
		if (food_ != nullptr)
			return true;
		else
			return false;
	}
}
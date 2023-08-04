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
			Food();
			return enums::eBTState::SUCCESS;
		}
		return enums::eBTState::FAILURE;
	}
	void FindFood::Food()
	{
		GameObject* guppy = _BlackBoard->GetData<GameObject>(L"Guppy");

		KdTree* kd = Mn::kdTree;
		kd->Query(guppy, 2.0f);
	}
}
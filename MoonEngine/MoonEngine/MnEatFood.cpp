#include "MnEatFood.h"
#include "MnGameObject.h"
#include "MnCollider2D.h"
#include "MnFood.h"
#include "MnAnimator.h"
#include "MnPlayAnimaion.h"

namespace Mn
{
	EatFood::EatFood()
		:_BlackBoard(nullptr)
	{
	}
	EatFood::EatFood(BlackBoard* board)
		:_BlackBoard(board)
	{
	}
	EatFood::~EatFood()
	{
	}
	enums::eBTState EatFood::Run()
	{
		Collider2D* food = _BlackBoard->GetData<Collider2D>(L"otherColl");
		if (food == nullptr)
			return enums::eBTState::FAILURE;
		Food* castFood = dynamic_cast<Food*>(food->GetOwner());
		_BlackBoard->EraseData<Collider2D>(L"otherColl");
		_BlackBoard->SetData(L"CollisionEnter", false);
		_BlackBoard->SetData(L"CollisionStay", false);
		_BlackBoard->SetData(L"HungryStack", 0);
		UINT stack = _BlackBoard->GetDataValue<UINT>(L"Level_Stack");
		stack += 1;
		_BlackBoard->SetData(L"Level_Stack", stack);
		castFood->State(GameObject::eState::Dead);
		

		return enums::eBTState::SUCCESS;
	}
}
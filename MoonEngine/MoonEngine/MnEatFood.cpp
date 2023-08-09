#include "MnEatFood.h"
#include "MnGameObject.h"
#include "MnCollider2D.h"
#include "MnFood.h"

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
		Food* castFood = dynamic_cast<Food*>(food->GetOwner());
		castFood->State(GameObject::eState::Dead);
		_BlackBoard->EraseData<Collider2D>(L"otherColl");
		_BlackBoard->SetData(L"CollisionEnter", false);
		_BlackBoard->SetData(L"CollisionStay", false);
		_BlackBoard->SetData(L"HungryStack", 0);
		_BlackBoard->SetData(L"Behavior", enums::eBehavior::Eat);
		return enums::eBTState::SUCCESS;
	}
}
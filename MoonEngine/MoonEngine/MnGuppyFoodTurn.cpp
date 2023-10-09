#include "MnGuppyFoodTurn.h"
#include "MnGameObject.h"
#include "MnAnimator.h"
#include "MnPlayAnimaion.h"
namespace Mn
{
	GuppyFoodTurn::GuppyFoodTurn()
		: _BlackBoard(nullptr)
	{
	}
	GuppyFoodTurn::GuppyFoodTurn(BlackBoard* board)
		: _BlackBoard(board)
	{
	}
	GuppyFoodTurn::~GuppyFoodTurn()
	{
	}
	enums::eBTState GuppyFoodTurn::Run()
	{
		PlayAnimaion* anima = new PlayAnimaion(_BlackBoard);
		GameObject* owner = _BlackBoard->GetData<GameObject>(L"Owner");
		Transform* tr = owner->GetComponent<Transform>();
		Vector3 ownerPos = tr->Position();
		Vector3 foodPos = _BlackBoard->GetDataValue<Vector3>(L"Food_Pos");

		enums::eDir dir = _BlackBoard->GetDataValue<enums::eDir>(L"Dir");
		enums::eDir foodDir;
		
		if (ownerPos != foodPos)
		{
			Vector3 MovePos = foodPos - ownerPos;
			if (foodPos.x - ownerPos.x < 0)
				foodDir = enums::eDir::Left;
			else
				foodDir = enums::eDir::Right;
			
			if (dir == enums::eDir::Right && foodDir == enums::eDir::Left)
			{
				_BlackBoard->SetData(L"Behavior", enums::eBehavior::Turn);
				anima->Run();
				_BlackBoard->SetData(L"Dir", enums::eDir::Left);
			}
			else if (dir == enums::eDir::Left && foodDir == enums::eDir::Right)
			{
				_BlackBoard->SetData(L"Behavior", enums::eBehavior::Turn);
				anima->Run();
				_BlackBoard->SetData(L"Dir", enums::eDir::Right);
			}
			
			_BlackBoard->SetData(L"Dir", foodDir);
		}
		return enums::eBTState::SUCCESS;
	}
}
#include "MnMove2Coin.h"
#include "MnGameObject.h"
#include "MnTime.h"
#include "MnAnimator.h"

namespace Mn
{
	Move2Coin::Move2Coin()
		: _BlackBoard(nullptr)
	{
	}
	Move2Coin::Move2Coin(BlackBoard* board)
		: _BlackBoard(board)
	{
	}
	Move2Coin::~Move2Coin()
	{
	}
	enums::eBTState Move2Coin::Run()
	{
		GameObject* stinky = _BlackBoard->GetData<GameObject>(L"Stinky");
		Transform* tr = stinky->GetComponent<Transform>();
		Vector3 pos = tr->Position();

		Vector3 Vec = _BlackBoard->GetDataValue<Vector3>(L"Nearest_Distance");
		Vector3 Norm = Vec;
		Norm.Normalize();

		enums::eDir dir = _BlackBoard->GetDataValue<enums::eDir>(L"Dir");
		Animator* at = stinky->GetComponent<Animator>();

		if (Vec.x > 0 && dir == enums::eDir::Left)
		{
			at->PlayAnimation(L"Stinky_Turn", true);
			_BlackBoard->SetData(L"Dir", enums::eDir::Right);
		}
		else if (Vec.x < 0 && dir == enums::eDir::Right)
		{
			at->PlayAnimation(L"Stinky_Turn_Reverse", true);
			_BlackBoard->SetData(L"Dir", enums::eDir::Left);
		}

		pos.x += (Norm.x * 0.5f * Time::DeltaTime());
		tr->Position(pos);
		return enums::eBTState::SUCCESS;
	}
}
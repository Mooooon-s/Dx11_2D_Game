#include "MnTurn2Food.h"
#include "MnGameObject.h"
#include "MnCaniBoarAnimatonCntrl.h"
#include "MnUltravoreAnimationCntrl.h"
#include "MnAnimator.h"

namespace Mn
{
	Turn2Food::Turn2Food()
		: _BlackBoard(nullptr)
	{
	}
	Turn2Food::Turn2Food(BlackBoard* board)
		:_BlackBoard(board)
	{
	}
	Turn2Food::~Turn2Food()
	{
	}
	enums::eBTState Turn2Food::Run()
	{
		GameObject* owner = _BlackBoard->GetData<GameObject>(L"Owner");

		Vector3 moveVec = _BlackBoard->GetDataValue<Vector3>(L"MoveVector");
		eDir dir = _BlackBoard->GetDataValue<eDir>(L"Dir");

		if (moveVec.x > 0 && dir == eDir::Left)
		{
			_BlackBoard->SetData(L"Behavior", eBehavior::Turn);
			AnimationPlay();
			_BlackBoard->SetData(L"Dir", eDir::Right);
		}
		else if(moveVec.x < 0 && dir == eDir::Right)
		{
			_BlackBoard->SetData(L"Behavior", eBehavior::Turn);
			AnimationPlay();
			_BlackBoard->SetData(L"Dir", eDir::Left);
		}
		return enums::eBTState::SUCCESS;
	}
	void Turn2Food::AnimationPlay()
	{
		eFishType type = _BlackBoard->GetDataValue<eFishType>(L"Fish_Type");
		switch (type)
		{
		case Mn::enums::eFishType::CaniBoar:
			_BlackBoard->GetData<CaniBoarAnimatonCntrl>(L"AnimaCntrl")->Run();
			break;
		case Mn::enums::eFishType::Ultravore:
			_BlackBoard->GetData<UltravoreAnimationCntrl>(L"AnimaCntrl")->Run();
			break;
		case Mn::enums::eFishType::End:
			break;
		default:
			break;
		}
	}
}
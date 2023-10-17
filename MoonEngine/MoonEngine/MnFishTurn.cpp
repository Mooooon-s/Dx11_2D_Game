#include "MnFishTurn.h"
#include "MnGameObject.h"
#include "MnAnimator.h"
#include "MnCaniBoarAnimatonCntrl.h"
#include "MnZorfAnimationCntrl.h"
#include "MnUltravoreAnimationCntrl.h"
#include "MnItchyAnimationCntrl.h"
#include "MnAmpAnimationCntrl.h"
#include "MnPregoAnimationCntrl.h"

namespace Mn
{
	FishTurn::FishTurn()
		: _BlackBoard(nullptr)
	{
	}
	FishTurn::FishTurn(BlackBoard* board)
		: _BlackBoard(board)
	{
	}
	FishTurn::~FishTurn()
	{
	}
	enums::eBTState FishTurn::Run()
	{
		GameObject* gameObj = _BlackBoard->GetData<GameObject>(L"Owner");
		Animator* at = gameObj->GetComponent<Animator>();

		if (at->AnimationComplete() && _BlackBoard->GetDataValue<eBehavior>(L"Behavior")== eBehavior::Turn)
		{
			enums::eDir dir = _BlackBoard->GetDataValue<enums::eDir>(L"Dir");
			if (dir == enums::eDir::Left)
				_BlackBoard->SetData<enums::eDir>(L"Dir", enums::eDir::Right);
			else
				_BlackBoard->SetData<enums::eDir>(L"Dir", enums::eDir::Left);

			_BlackBoard->SetData(L"Behavior", enums::eBehavior::Swim);

			//animation run
			AnimationPlay();

			_BlackBoard->ResetRunningNode();
			return enums::eBTState::SUCCESS;
		}
		else
		{
			_BlackBoard->SetRunningNode<FishTurn>(this);
			return enums::eBTState::RUNNING;
		}
	}
	void FishTurn::AnimationPlay()
	{
		eFishType type = _BlackBoard->GetDataValue<eFishType>(L"Fish_Type");
		switch (type)
		{
		case Mn::enums::eFishType::Guppy:
			break;
		case Mn::enums::eFishType::CaniBoar:
			_BlackBoard->GetData<CaniBoarAnimatonCntrl>(L"AnimaCntrl")->Run();
			break;
		case Mn::enums::eFishType::Zorf:
			_BlackBoard->GetData<ZorfAnimationCntrl>(L"AnimaCntrl")->Run();
			break;
		case Mn::enums::eFishType::Ultravore:
			_BlackBoard->GetData<UltravoreAnimationCntrl>(L"AnimaCntrl")->Run();
			break;
		case Mn::enums::eFishType::Itchy:
			_BlackBoard->GetData<ItchyAnimationCntrl>(L"AnimaCntrl")->Run();
			break;
		case Mn::enums::eFishType::Prego:
			_BlackBoard->GetData<PregoAnimationCntrl>(L"AnimaCntrl")->Run();
			break;
		case Mn::enums::eFishType::Amp:
			_BlackBoard->GetData<AmpAnimationCntrl>(L"AnimaCntrl")->Run();
			break;
		case Mn::enums::eFishType::End:
			break;
		default:
			break;
		}
	}
}
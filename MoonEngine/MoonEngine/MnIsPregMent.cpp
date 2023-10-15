#include "MnIsPregMent.h"
#include "MnTime.h"
#include "MnPregoAnimationCntrl.h"
#include "MnGameObject.h"
#include "MnAnimator.h"

namespace Mn
{
	IsPregMent::IsPregMent()
		: _BlackBoard(nullptr)
		, _Flag(1)
	{
	}
	IsPregMent::IsPregMent(BlackBoard* board)
		: _BlackBoard(board)
		, _Flag(1)
	{
	}
	IsPregMent::~IsPregMent()
	{
	}
	enums::eBTState IsPregMent::Run()
	{
		float time = _BlackBoard->GetDataValue<float>(L"Timer");
		if (_BlackBoard->GetDataValue<bool>(L"PregMent"))
		{
			return enums::eBTState::SUCCESS;
		}
		else
		{
			_Time = _BlackBoard->GetDataValue<float>(L"BirthTime");
			float calculateTime = time - _Time;
			if (calculateTime >= 15.0f)
			{
				if (_Flag)
				{
					_BlackBoard->GetData<PregoAnimationCntrl>(L"AnimaCntrl")->GetPregMent();
					_Flag = 0;
				}
				GameObject* owner = _BlackBoard->GetData<GameObject>(L"Owner");
				Animator* at = owner->GetComponent<Animator>();
				
				if (at->AnimationComplete())
				{
					_Flag = 1;
					_BlackBoard->SetData(L"PregMent", true);
					_BlackBoard->SetData(L"PregMentTime", time);
					_BlackBoard->ResetRunningNode();
					return enums::eBTState::SUCCESS;
				}
				else
				{
					_BlackBoard->SetRunningNode(this);
					return enums::eBTState::RUNNING;
				}
			}
			else
			{
				return enums::eBTState::FAILURE;
			}
		}
	}
}
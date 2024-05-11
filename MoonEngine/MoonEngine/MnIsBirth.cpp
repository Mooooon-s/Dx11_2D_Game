#include "MnIsBirth.h"
#include "MnPregoAnimationCntrl.h"

#include "MnGameObject.h"
#include "MnAnimator.h"
#include "MnGuppy.h"
#include "MnObject.h"

namespace Mn
{
	IsBirth::IsBirth()
		: _BlackBoard(nullptr)
		, _Flag(1)
		, _ZPosition(0.0001)
	{
	}
	IsBirth::IsBirth(BlackBoard* board)
		: _BlackBoard(board)
		, _Flag(1)
		, _ZPosition(0.0001)
	{
	}
	IsBirth::~IsBirth()
	{
	}
	enums::eBTState IsBirth::Run()
	{
		float time = _BlackBoard->GetDataValue<float>(L"PregMentTime");
		float roottime = _BlackBoard->GetDataValue<float>(L"Timer");

		float calculateTime = roottime - time;
		if (calculateTime >= 15.0f)
		{
			GameObject* owner = _BlackBoard->GetData<GameObject>(L"Owner");
			Animator* at = owner->GetComponent<Animator>();

			if (_Flag)
			{
				_BlackBoard->GetData<PregoAnimationCntrl>(L"AnimaCntrl")->EndPregMent();
				_Flag = 0;
			}
			if (at->AnimationComplete())
			{
				Birthguupy();
				_Flag = 1;
				_BlackBoard->SetData(L"BirthTime", roottime);
				_BlackBoard->SetData(L"PregMent", false);
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
	void IsBirth::Birthguupy()
	{
		Resources::Load<AudioClip>(L"Prego_Birth", L"..\\Resources\\Sound\\fart.wav")->SoundPlay();
		GameObject* owner = _BlackBoard->GetData<GameObject>(L"Owner");
		Transform* tr = owner->GetComponent<Transform>();
		Vector3 pos = tr->Position();
		pos.z += _ZPosition;
		_ZPosition += 0.0001;

		Guppy* guppy = object::Instantiate<Guppy>(pos, eLayerType::Fish);
		guppy->Initialize();
	}
}
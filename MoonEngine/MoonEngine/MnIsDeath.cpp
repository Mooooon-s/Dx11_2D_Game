#include "MnIsDeath.h"
#include "MnGameObject.h"
#include "MnCaniBoarAnimatonCntrl.h"

namespace Mn
{
	IsDeath::IsDeath()
		: _BlackBoard(nullptr)
		, _Flag(0)
	{
	}
	IsDeath::IsDeath(BlackBoard* board)
		: _BlackBoard(board)
		, _Flag(0)
	{
	}
	IsDeath::~IsDeath()
	{
	}
	enums::eBTState IsDeath::Run()
	{
		if (_Flag)
		{
			_BlackBoard->SetRunningNode<IsDeath>(this);
			return eBTState::RUNNING;
		}

		eFishState state = _BlackBoard->GetDataValue<eFishState>(L"Fish_State");

		int hungrystack = _BlackBoard->GetDataValue<int>(L"HungryStack");
		if (hungrystack <= -10)
		{
			if (state != eFishState::Death)
			{
				_BlackBoard->SetData(L"Fish_State", eFishState::Death);
				AnimationPlay();
				_Flag = 1;
				_BlackBoard->SetRunningNode<IsDeath>(this);
				return eBTState::RUNNING;
			}
			else
				return enums::eBTState::FAILURE;
		}
		return enums::eBTState::FAILURE;
	}
	void IsDeath::AnimationPlay()
	{
		eFishType type = _BlackBoard->GetDataValue<eFishType>(L"Fish_Type");
		switch (type)
		{
		case Mn::enums::eFishType::CaniBoar:
			_BlackBoard->GetData<CaniBoarAnimatonCntrl>(L"AnimaCntrl")->Run();
			break;
		case Mn::enums::eFishType::End:
			break;
		}
	}
}
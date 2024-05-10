#include "MnAddLevel.h"
#include "MnGameObject.h"
#include "MnPlayAnimaion.h"
#include "MnResources.h"
#include "MnAudioClip.h"

namespace Mn
{
	AddLevel::AddLevel()
		:_BlackBoard(nullptr)
	{
	}
	AddLevel::AddLevel(BlackBoard* board)
		:_BlackBoard(board)
	{
	}
	AddLevel::~AddLevel()
	{
	}
	enums::eBTState AddLevel::Run()
	{
		UINT stack = _BlackBoard->GetDataValue<UINT>(L"Level_Stack");
		UINT level = _BlackBoard->GetDataValue<UINT>(L"Level");

		switch (level)
		{
		case 1:
			if (stack >= 3)
			{
				_BlackBoard->SetData(L"Level_Stack", 0);
				_BlackBoard->SetData(L"Level", 2);
				Resources::Find<Mn::AudioClip>(L"Grow")->Play();
			}
			break;
		case 2:
			if (stack >= 3)
			{
				_BlackBoard->SetData(L"Level_Stack", 0);
				_BlackBoard->SetData(L"Level", 3);
				Resources::Find<Mn::AudioClip>(L"Grow")->Play();
			}
			break;
		case 3:
			if (stack >= 3)
			{
				_BlackBoard->SetData(L"Level_Stack", 0);
			}
			break;
		default:
			break;
		}

		PlayAnimaion* anima = new PlayAnimaion(_BlackBoard);
		anima->Run();

		return enums::eBTState::SUCCESS;
	}
}
#include "MnMonIsDead.h"
#include "MnGameObject.h"
#include "MnTime.h"

namespace Mn
{
	MonIsDead::MonIsDead()
		: _BlackBoard(nullptr)
		, _Flag(false)
	{
	}
	MonIsDead::MonIsDead(BlackBoard* board)
		: _BlackBoard(board)
	{
	}
	MonIsDead::~MonIsDead()
	{
	}
	enums::eBTState MonIsDead::Run()
	{
		int hp = _BlackBoard->GetDataValue<int>(L"Hp");
		if (hp <= 0)
		{
			GameObject* owner = _BlackBoard->GetData<GameObject>(L"Owner");
			float alpha = _BlackBoard->GetDataValue<float>(L"Alpha");
			alpha -= 0.7 * Time::DeltaTime();
			_BlackBoard->SetData(L"Alpha", alpha);

			if (alpha <= 0.0f)
			{
				SoundChange();
				owner->State(GameObject::eState::Dead);
				_BlackBoard->ResetRunningNode();
				return enums::eBTState::SUCCESS;
			}
			else
			{
				if (!_Flag)
				{
					Resources::Find<AudioClip>(L"ROAR")->SoundPlay();
					_Flag = true;
				}
				Vector3 pos = owner->GetComponent<Transform>()->Position();
				pos -= Vector3(0.0f, 0.2f, 0.0f) * Time::DeltaTime();
				owner->GetComponent<Transform>()->Position(pos);
				_BlackBoard->SetRunningNode<MonIsDead>(this);
				return enums::eBTState::RUNNING;
			}
		}
		else
			return enums::eBTState::FAILURE;
	}
	void MonIsDead::SoundChange()
	{
		Resources::Find<AudioClip>(L"Alien_music")->Stop();
		Resources::Find<AudioClip>(L"Stage_BackGround_Music")->SetVolum(0.3f);
	}
}
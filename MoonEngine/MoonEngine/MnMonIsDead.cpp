#include "MnMonIsDead.h"
#include "MnGameObject.h"
#include "MnTime.h"
namespace Mn
{
	MonIsDead::MonIsDead()
		: _BlackBoard(nullptr)
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
				owner->State(GameObject::eState::Dead);
				_BlackBoard->ResetRunningNode();
				return enums::eBTState::SUCCESS;
			}
			else
			{
				Vector3 pos = owner->GetComponent<Transform>()->Position();
				pos -= Vector3(0.0f, 0.2f, 0.0f) * Time::DeltaTime();
				owner->GetComponent<Transform>()->Position(pos);
				_BlackBoard->SetRunningNode<MonIsDead>(this);
			}
		}
		else
			return enums::eBTState::FAILURE;
	}
}
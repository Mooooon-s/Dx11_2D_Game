#include "MnBalIsDead.h"
#include "MnGameObject.h"

namespace Mn
{
	BalIsDead::BalIsDead()
		: _BlackBoard(nullptr)
	{
	}
	BalIsDead::BalIsDead(BlackBoard* board)
		: _BlackBoard(board)
	{
	}
	BalIsDead::~BalIsDead()
	{
	}
	enums::eBTState BalIsDead::Run()
	{
		GameObject* balrog = _BlackBoard->GetData<GameObject>(L"Balrog");
		int hp = _BlackBoard->GetDataValue<int>(L"Hp");
		if (hp <= 0)
		{
			balrog->State(GameObject::eState::Dead);
			return enums::eBTState::SUCCESS;
		}
		else
			return enums::eBTState::FAILURE;
	}
}
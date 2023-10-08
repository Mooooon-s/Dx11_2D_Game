#include "MnMonIsDead.h"
#include "MnGameObject.h"

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
		GameObject* balrog = _BlackBoard->GetData<GameObject>(L"Owner");
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
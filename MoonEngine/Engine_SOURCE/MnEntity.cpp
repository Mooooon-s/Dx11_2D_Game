#include "MnEntity.h"

namespace Mn
{
	Entity::Entity()
		: _Name(L"")
		, _ID((UINT64)this)
	{
	}

	Entity::~Entity()
	{
	}
}
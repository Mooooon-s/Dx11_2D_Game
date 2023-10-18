#pragma once
#include "MnObject.h"
#include "MnGameObject.h"

namespace Mn
{
	template <typename T>
	T* CreateIcon(Vector3 pos)
	{
		T* icon = object::Instantiate<T>(pos, eLayerType::UI);
		return icon;
	}
}
#pragma once
#include "MnEntity.h"

namespace Mn
{
	using namespace Mn::enums;
	class Component : public Entity
	{
	private:
		const eComponentType _Type;
	public:
		Component();
		~Component();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();
	};

}

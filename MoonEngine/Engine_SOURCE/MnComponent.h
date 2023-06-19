#pragma once
#include "MnEntity.h"

namespace Mn
{
	using namespace Mn::enums;
	using namespace Mn::math;
	class GameObject;
	class Component : public Entity
	{
	private:
		const eComponentType _Type;
		GameObject* _Owner;
	public:
		Component(eComponentType type);
		~Component();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();

		GameObject* GetOwner() { return _Owner; }
		void SetOwner(GameObject* owner) { _Owner = owner; }
	};

}

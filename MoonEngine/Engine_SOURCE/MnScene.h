#pragma once
#include "MnEntity.h"
#include "MnGameObject.h"

namespace Mn
{
	class Scene : public Entity
	{
	private:
		std::vector<GameObject*> _GameObjects;
	public:
		Scene();
		virtual ~Scene();
		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();
	};
}


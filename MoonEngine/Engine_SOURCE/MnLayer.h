#pragma once
#include "MnGameObject.h"

namespace Mn
{
	class Layer
	{
	private:
		std::vector<GameObject*> _GameObjects;
	public:
		Layer();
		~Layer();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();
		virtual void Destroy();

	public:
		void AddGameObject(GameObject* gameObj);
		const std::vector<GameObject*> GetGameObjects()
		{
			return _GameObjects;
		}
	};

}

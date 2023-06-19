#pragma once
#include "MnEntity.h"
#include "MnLayer.h"

namespace Mn
{
	class Scene : public Entity
	{
	private:
		std::vector<Layer> _Layers;
	public:
		Scene();
		virtual ~Scene();
		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();

		virtual void OnEnter();
		virtual void OnExit();

	public:
		void AddGameObject(eLayerType type, GameObject* gameObj);
	};
}


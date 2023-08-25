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
		virtual void FontRender();
		virtual void Destroy();

		virtual void OnEnter();
		virtual void OnExit();

	public:
		void AddGameObject(eLayerType type, GameObject* gameObj);

		template <typename T>
		std::vector<T*> FindObjectsOfType()
		{
			std::vector<T*> findObjs = {};
			for (Layer* layer : _Layers)
			{
				auto gameObjs = layer->GetGameObjects();
				for (GameObject* obj : gameObjs)
				{
					T* buff = dynamic_cast<T*>(obj);
					if (buff != nullptr)
						findObjs.push_back(buff);
				}
			}

			return findObjs;
		}

		Layer& GetLayer(eLayerType type) { return _Layers[(UINT)type]; }
	};
}


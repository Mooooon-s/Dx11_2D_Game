#pragma once
#include "MnEntity.h"
#include "MnComponent.h"
namespace Mn
{
	class GameObject : public Entity
	{
	public:
		enum eState
		{
			Active,
			Paused,
			Dead,
		};
	private:
		eState _State;
		std::vector<Component*> _Components;
	public:
		GameObject();
		virtual ~GameObject();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();
	public:
		template <typename T>
		T* GetComponent()
		{
			T* component;
			for (T* comp : _Components)
			{
				component = dynamic_cast<T*>(comp);
				if (component != nullptr)
					return component;
			}

			return nullptr;
		}
		template <typename T>
		T* AddComponent()
		{
			T* comp = new T();
			Component* buff = dynamic_cast<Component*>(comp);

			if (buff == nullptr)
				return nullptr;

			_Components.push_back(buff);
			
			return comp;
		}
	};
}


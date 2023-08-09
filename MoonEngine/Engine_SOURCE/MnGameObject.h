#pragma once
#include "MnEntity.h"
#include "MnComponent.h"
#include "MnScript.h"

namespace Mn
{
	class GameObject : public Entity
	{
	public:
		enum class eState
		{
			Active,
			Paused,
			Dead,
		};
	private:
		eState _State;
		std::vector<Component*> _Components;
		std::vector<Script*>	_Scripts;

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
			for (Component* comp : _Components)
			{
				component = dynamic_cast<T*>(comp);
				if (component != nullptr)
					return component;
			}

			for (Script* script : _Scripts)
			{
				component = dynamic_cast<T*>(script);
				if (component != nullptr)
					return component;
			}

			return nullptr;
		}
		template <typename T>
		const std::vector<T*> GetComponents()
		{
			std::vector<T*> comps;

			T* component;
			for (Component* comp : _Components)
			{
				component = dynamic_cast<T*>(comp);
				if (component != nullptr)
					comps.push_back(component);
			}

			for (Script* script : _Scripts)
			{
				component = dynamic_cast<T*>(script);
				if (component != nullptr)
					comps.push_back(component);
			}

			return comps;
		}

		template <typename T>
		T* AddComponent()
		{
			T* comp = new T();
			Component* buff = dynamic_cast<Component*>(comp);
			Script* script = dynamic_cast<Script*>(buff);

			if (buff == nullptr)
				return nullptr;

			if (script == nullptr)
				_Components.push_back(buff);
			else
				_Scripts.push_back(script);
			comp->SetOwner(this);
			comp->Initialize();
			return comp;
		}

	public:
		void State(eState state) { _State = state; }
		eState State() { return _State; }
	};
}


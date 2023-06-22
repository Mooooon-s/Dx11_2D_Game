#include "MnGameObject.h"
#include "MnRenderer.h"
#include "MnGraphicDevice_Dx11.h"
#include "MnTransform.h"
namespace Mn
{
	GameObject::GameObject()
		:_State(eState::Active)
	{
		AddComponent<Transform>();
	}
	GameObject::~GameObject()
	{
		for (Component* comp : _Components)
		{
			if (comp == nullptr)
				continue;

			delete comp;
			comp = nullptr;
		}

		for (Script* script : _Scripts)
		{
			if (script == nullptr)
				continue;

			delete script;
			script = nullptr;
		}
	}
	void GameObject::Initialize()
	{
	}
	void GameObject::Update()
	{
		for (Component* comp : _Components)
		{
			comp->Update();
		}

		for (Script* script : _Scripts)
		{
			script->Update();
		}
	}
	void GameObject::LateUpdate()
	{
		for (Component* comp : _Components)
		{
			comp->LateUpdate();
		}

		for (Script* script : _Scripts)
		{
			script->LateUpdate();
		}
	}
	void GameObject::Render()
	{
		for (Component* comp : _Components)
		{
			comp->Render();
		}

		for (Script* script : _Scripts)
		{
			script->Render();
		}
	}
}
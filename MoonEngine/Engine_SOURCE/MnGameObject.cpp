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
		for (Component* comp : _Components)
		{
			if (comp == nullptr)
				continue;
			comp->Initialize();
		}

		for (Script* script : _Scripts)
		{
			if (script == nullptr)
				continue;
			script->Initialize();
		}
	}
	void GameObject::Update()
	{
		for (Component* comp : _Components)
		{
			if (comp == nullptr)
				continue;
			comp->Update();
		}

		for (Script* script : _Scripts)
		{
			if (script == nullptr)
				continue;

			script->Update();
		}
	}
	void GameObject::LateUpdate()
	{
		for (Component* comp : _Components)
		{
			if (comp == nullptr)
				continue;
			comp->LateUpdate();
		}

		for (Script* script : _Scripts)
		{
			if (script == nullptr)
				continue;
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
	void GameObject::FontRender()
	{
	}
	void GameObject::OnClick()
	{
	}
	void GameObject::OnClick(Vector3 pos)
	{
	}
	void GameObject::MouseOn()
	{
	}
	void GameObject::MouseOff()
	{
	}
}
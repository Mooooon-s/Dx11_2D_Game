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
	}
	void GameObject::LateUpdate()
	{
		for (Component* comp : _Components)
		{
			comp->LateUpdate();
		}
	}
	void GameObject::Render()
	{
		for (Component* comp : _Components)
		{
			comp->Render();
		}
	}
}
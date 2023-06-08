#include "MnGameObject.h"
#include "MnRenderer.h"
#include "MnGraphicDevice_Dx11.h"

namespace Mn
{
	GameObject::GameObject()
		:_State(eState::Active)
	{
	}
	GameObject::~GameObject()
	{
	}
	void GameObject::Initialize()
	{
	}
	void GameObject::Update()
	{
	}
	void GameObject::LateUpdate()
	{
	}
	void GameObject::Render()
	{
	}
}
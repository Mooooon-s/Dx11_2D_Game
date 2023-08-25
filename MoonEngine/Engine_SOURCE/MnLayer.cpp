#include "MnLayer.h"
namespace Mn
{
	Layer::Layer()
	{
	}
	Layer::~Layer()
	{
		for (GameObject* gameObj : _GameObjects)
		{
			if (gameObj == nullptr)
				continue;

			delete gameObj;
			gameObj = nullptr;
		}
	}
	void Layer::Initialize()
	{
	}
	void Layer::Update()
	{
		for (GameObject* gameObj : _GameObjects)
		{
			if (gameObj->State() != GameObject::eState::Active)
				continue;
			gameObj->Update();
		}
	}
	void Layer::LateUpdate()
	{
		for (GameObject* gameObj : _GameObjects)
		{
			if (gameObj->State() != GameObject::eState::Active)
				continue;
			gameObj->LateUpdate();
		}
	}
	void Layer::Render()
	{
		for (GameObject* gameObj : _GameObjects)
		{
			if (gameObj->State() != GameObject::eState::Active)
				continue;
			gameObj->Render();
		}
	}
	void Layer::FontRender()
	{
		for (GameObject* gameObj : _GameObjects)
		{
			if (gameObj->State() != GameObject::eState::Active)
				continue;
			gameObj->FontRender();
		}
	}
	void Layer::Destroy()
	{
		std::set<GameObject*> deleteGameObj = {};
		for (GameObject* gameObj : _GameObjects)
		{
			if (gameObj->State() == GameObject::eState::Dead)
				deleteGameObj.insert(gameObj);
		}

		// daed 오브젝트 제외시키기 layer에서
		typedef std::vector<GameObject*>::iterator GameObjectIter;
		for (GameObjectIter iter = _GameObjects.begin()
			; iter != _GameObjects.end(); )
		{
			std::set<GameObject*>::iterator deleteIter
				= deleteGameObj.find(*(iter));

			if (deleteIter != deleteGameObj.end())
			{
				iter = _GameObjects.erase(iter);
				continue;
			}

			iter++;
		}

		//메모리 해제
		for (GameObject* gameObj : deleteGameObj)
		{
			delete gameObj;
			gameObj = nullptr;
		}
	}
	void Layer::AddGameObject(GameObject* gameObj)
	{
		_GameObjects.push_back(gameObj);
	}
}
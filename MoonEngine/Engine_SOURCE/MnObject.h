#pragma once
#include "MnLayer.h"
#include "MnGameObject.h"
#include "MnScene.h"
#include "MnSceneManager.h"
#include "MnTransform.h"
#include "MnMaterial.h"
#include "MnTexture.h"
#include "MnComponent.h"
#include "MnMeshRenderer.h"

namespace Mn::object
{
	template<typename T>
	static __forceinline T* Instantiate(enums::eLayerType layer)
	{
		T* gameObj = new T();
		Scene* scene = SceneManager::ActiveScene();
		scene->AddGameObject(layer, gameObj);
		return gameObj;
	}

	template <typename T>
	static __forceinline T* Instantiate(Vector3 pos, enums::eLayerType layer)
	{
		T* gameObj = new T();
		Transform* tr = gameObj->GetComponent<Transform>();
		tr->Position(pos);

		Scene* scene = SceneManager::ActiveScene();
		scene->AddGameObject(layer, gameObj);

		return gameObj;
	}

	template <typename T>
	static __forceinline T* Instantiate(Vector3 pos, Vector3 rotate, enums::eLayerType layer)
	{
		T* gameObj = new T();
		Transform* tr = gameObj->GetComponent<Transform>();
		tr->Position(pos);
		tr->Rotation(rotate);

		Scene* scene = SceneManager::ActiveScene();
		scene->AddGameObject(layer, gameObj);

		return gameObj;
	}

	template <typename T>
	static __forceinline T* Instantiate(Vector3 pos, Vector3 rotate, Vector3 scale, enums::eLayerType layer)
	{
		T* gameObj = new T();
		Transform* tr = gameObj->GetComponent<Transform>();
		tr->Position(pos);
		tr->Rotation(rotate);
		tr->Scale(scale);

		Scene* scene = SceneManager::ActiveScene();
		scene->AddGameObject(layer, gameObj);
		return gameObj;
	}

	template<typename T>
	static __forceinline T* Instantiate(enums::eLayerType layer,Scene* activeScene)
	{
		T* gameObj = new T();
		Scene* scene = activeScene;
		scene->AddGameObject(layer, gameObj);
		return gameObj;
	}

	template <typename T>
	static __forceinline T* Instantiate(std::wstring mesh, std::wstring material ,enums::eLayerType layer)
	{
		T* gameObj = new T();
		MeshRenderer* mr = gameObj->AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(mesh));
		mr->SetMaterial(Resources::Find<Material>(material));

		Scene* scene = SceneManager::ActiveScene();
		scene->AddGameObject(layer, gameObj);

		return gameObj;
	}

	static __forceinline void Destroy(GameObject* gameObj)
	{
		gameObj->State(Mn::GameObject::eState::Dead);
	}
}

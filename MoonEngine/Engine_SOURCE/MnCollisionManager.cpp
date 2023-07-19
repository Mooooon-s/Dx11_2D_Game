#include "MnCollisionManager.h"
#include "MnSceneManager.h"
#include "MnCollider2D.h"

#include "MnMeshRenderer.h"
#include "MnResources.h"
#include "MnConstantBuffer.h"
#include "MnRenderer.h"

namespace Mn
{
	std::bitset<LAYER_MAX> CollisionManager::_Matrix[LAYER_MAX];
	std::map<UINT64, bool> CollisionManager::_CollisionMap;

	
	void CollisionManager::Initialize()
	{
	}

	void CollisionManager::Update()
	{
		for (UINT column = 0; column < (UINT)eLayerType::End; column++)
		{
			for (UINT row = 0; row < (UINT)eLayerType::End; row++)
			{
				if (_Matrix[row][column] == true)
				{
					LayerCollision((eLayerType)column, (eLayerType)row);
				}
			}
		}
	}

	void CollisionManager::LayerCollision(eLayerType left, eLayerType right)
	{
		Scene* activeScene = SceneManager::ActiveScene();

		const std::vector<GameObject*>& lefts = activeScene->GetLayer(left).GetGameObjects();
		const std::vector<GameObject*>& rights = activeScene->GetLayer(right).GetGameObjects();

		for (GameObject* leftObj : lefts)
		{
			Collider2D* leftCol = leftObj->GetComponent<Collider2D>();
			if (leftCol == nullptr)
				continue;
			if (leftObj->State() != GameObject::eState::Active)
				continue;

			for (GameObject* rightObj : rights)
			{
				Collider2D* rightCol = rightObj->GetComponent<Collider2D>();
				if (rightCol == nullptr)
					continue;
				if (rightObj->State() != GameObject::eState::Active)
					continue;

				ColliderCollision(leftCol, rightCol);
			}
		}

	}

	void CollisionManager::ColliderCollision(Collider2D* left, Collider2D* right)
	{
		ColliderID id = {};
		id.left = left->GetColliderID();
		id.right = right->GetColliderID();

		std::map<UINT64, bool>::iterator iter = _CollisionMap.find(id.id);

		if (iter == _CollisionMap.end())
		{
			_CollisionMap.insert(std::make_pair(id.id, false));
			iter = _CollisionMap.find(id.id);
		}

		if (Intersect(left, right))
		{

			if (iter->second == false)
			{
				left->OnCollisionEnter(right);
				right->OnCollisionEnter(left);
			}
			else
			{
				left->OnCollisionStay(right);
				right->OnCollisionStay(left);
			}
		}
		else
		{

			if (iter->second == true)
			{
				left->OnCollisionExit(right);
				right->OnCollisionExit(left);
			}

			
		}

	}

	bool CollisionManager::Intersect(Collider2D* left, Collider2D* right)
	{

		if (left->GetDebugMesh().type == eColliderType::Circle && right->GetDebugMesh().type == eColliderType::Circle)
		{
			//원 - 원 충돌
			Vector3 v1 = right->GetPosition() - left->GetPosition();
			float dist = std::sqrtf((v1.x * v1.x) + (v1.y * v1.y));
			float r1 = 0.5 * right->GetScale().x;
			float r2 = 0.5 * right->GetScale().x;
			if (dist < (r1 + r2))
				return true;
		}
		else
		{
			//네모네모 충돌
			//분리축 이론
			Vector3 d = left->GetPosition() - right->GetPosition();
			Vector3 v[4]; 
			Vector3 uint;
			v[0] = left->HeightVector();
			v[1] = right->HeightVector();
			v[2] = left->WidthVector();
			v[3] = right->WidthVector();

			for (int i = 0; i < 4; i++)
			{
				float sum = 0;
				uint = v[i];
				uint.Normalize();
				for (int i = 0; i < 4; i++)
				{
					float c = std::abs(v[i].Dot(uint));
					sum += std::abs(v[i].Dot(uint));
				}
				if (std::abs(d.Dot(uint)) > sum)
					return false;
			}
			return true;
		}
		return false;
	}

	void CollisionManager::SetLayer(eLayerType left, eLayerType right, bool enable)
	{
		UINT row = -1;
		UINT col = -1;

		UINT iLeft = (UINT)left;
		UINT iRight = (UINT)right;

		if (iLeft <= iRight)
		{
			row = iLeft;
			col = iRight;
		}
		else
		{
			row = iRight;
			col = iLeft;
		}

		_Matrix[col][row] = enable;
	}

	void CollisionManager::Clear()
	{
		_Matrix->reset();
		_CollisionMap.clear();
	}
}
#include "MnMousePosScript.h"

#include "../Engine_SOURCE/MnApplication.h"
#include "../Engine_SOURCE/MnInput.h"

#include "MnObject.h"
#include "MnGameObject.h"
#include "MnFood.h"
#include "MnInput.h"

#include "MnMoney.h"

extern Mn::Application application;

namespace Mn
{
	MousePosScript::MousePosScript()
		: _Cam(nullptr)
		, _Idx(1)
		, _GameObjects{}
		, _FoodLevel(1)
		, _FoodCount(3)
	{
		_Setting.reset();
		_Setting.set((UINT)eLayerType::Coin, 1);
		_Setting.set((UINT)eLayerType::Pet, 1);
		_Setting.set((UINT)eLayerType::Monster, 1);
		_Setting.set((UINT)eLayerType::UI, 1);
		_Setting.set((UINT)eLayerType::Button, 1);
	}
	MousePosScript::MousePosScript(GameObject* cam)
		: _Cam(cam)
		, _Idx(1)
		, _GameObjects{}
		, _FoodLevel(1)
		, _FoodCount(3)
	{
		_Setting.reset();
		_Setting.set((UINT)eLayerType::Coin, 1);
		_Setting.set((UINT)eLayerType::Pet, 1);
		_Setting.set((UINT)eLayerType::Monster, 1);
		_Setting.set((UINT)eLayerType::UI, 1);
		_Setting.set((UINT)eLayerType::Button, 1);
	}
	MousePosScript::~MousePosScript()
	{
	}
	void MousePosScript::Initialize()
	{

	}
	void MousePosScript::Update()
	{
		Scene* scene = SceneManager::ActiveScene();
		if (scene->GetName() == L"PlayScene")
		{
			PlaySceneMouse();
		}
		if (scene->GetName() == L"MenuScene")
		{
			MenuSceneMouse();
		}
		if (scene->GetName() == L"TitleScene")
		{
			TitleSceneMouse();
		}
	}
	void MousePosScript::LateUpdate()
	{
		
		_UnProjectPos = CalculatePos();

		HWND hwnd = application.GetHwnd();
		wchar_t szPos[50] = {};

		//프레임 계산
		swprintf_s(szPos, 50, L"x : %lf, y : %lf", _UnProjectPos.x, _UnProjectPos.y);
		SetWindowText(hwnd, szPos);

		_GameObjects.clear();
		_InterSectObjs.clear();
	}
	void MousePosScript::Render()
	{
	}
	Vector3 MousePosScript::CalculatePos()
	{
		Transform* tr = _Cam->GetComponent<Transform>();
		Matrix world = tr->WorldMatrix();
		Matrix view = tr->ViewMatrix();
		Matrix projection = tr->ProjectionMatrix();
		//camera
		Vector2 pos = Input::GetMousePos();
		_WinPos = Vector3(pos.x, pos.y, 1.0f);
		Viewport viewport;
		viewport.width = application.GetWidth();
		viewport.height = application.GetHeight();
		viewport.x = 0;
		viewport.y = 0;
		viewport.minDepth = 0.0f;
		viewport.maxDepth = 1.0f;

		return viewport.Unproject(_WinPos, Camera::GetGpuProjectionMatrix(), Camera::GetGpuViewMatrix(), Matrix::Identity);

	}
	void MousePosScript::InterSect(Collider2D* coll)
	{
		Vector3 pos = coll->GetPosition();
		Vector3 height = coll->HeightVector();
		Vector3 width =  coll->WidthVector();

		Vector3 Max = pos + height + width;
		Vector3 Min = pos - height - width;

		if (_DotPos.x >= Min.x && _DotPos.x <= Max.x
			&& _DotPos.y >= Min.y && _DotPos.y <= Max.y)
		{
			_InterSectObjs.push_back(coll->GetOwner());
		}
	}
	void MousePosScript::GatherObject()
	{
		Scene* scene = SceneManager::ActiveScene();
		for (int i = 0; i < (UINT)eLayerType::End; i++)
		{
			if (_Setting[i] == true)
			{
				std::vector<GameObject*> LayerObj = scene->GetLayer(eLayerType(i)).GetGameObjects();
				for (auto Obj : LayerObj)
				{
					if(Obj->GetComponent<Collider2D>()!=nullptr)
						_GameObjects.push_back(Obj);
				}
			}
		}
	}
	GameObject* MousePosScript::PrimaryObj()
	{
		if(_InterSectObjs.size()==0)
			return nullptr;

		GameObject* primaryObj = nullptr;

		for (auto obj : _InterSectObjs)
		{
			if (primaryObj == nullptr)
				primaryObj = obj;
			
			Vector3 ObjPos = obj->GetComponent<Transform>()->Position();
			Vector3 PriPos = primaryObj->GetComponent<Transform>()->Position();

			if (ObjPos.z < PriPos.z)
				primaryObj = obj;
		}

		return primaryObj;
	}
	void MousePosScript::FeedFood()
	{
		if (!MaxFood())
			return;
		if (_UnProjectPos.x > -2.0f && _UnProjectPos.x < 2.0f
			&& _UnProjectPos.y > -1.5f && _UnProjectPos.y < 1.0f)
		{
			if (MoneyCheck())
			{
				float a = (0.0001 * _Idx) + 1;
				Vector3 pos = Vector3(_UnProjectPos.x, _UnProjectPos.y, a);
				Food* food = object::Instantiate<Food>(pos, eLayerType::Food);
				food->FoodLevel(_FoodLevel);
				food->Initialize();
				_Idx += 1;
				if (_Idx >= 100)
					_Idx = 1;
			}
		}
	}
	void MousePosScript::FoodLevel()
	{
		if (_FoodLevel < 3)
			_FoodLevel++;
	}
	void MousePosScript::FoodCount()
	{
		if (_FoodCount < 5)
			_FoodCount++;
	}
	bool MousePosScript::MaxFood()
	{
		Scene* scene = SceneManager::ActiveScene();
		std::vector<GameObject*> food = scene->GetLayer(eLayerType::Food).GetGameObjects();
		if (food.size() < _FoodCount)
			return true;
		else
			return false;
	}
	bool MousePosScript::MoneyCheck()
	{
		Scene* scene = SceneManager::ActiveScene();
		std::vector<GameObject*> moneyObj = scene->GetLayer(eLayerType::UI).GetGameObjects();
		for (auto obj : moneyObj)
		{
			if (dynamic_cast<Money*>(obj))
			{
				if (dynamic_cast<Money*>(obj)->UseableMoney(5))
				{
					dynamic_cast<Money*>(obj)->UseMoney(5);
					return true;
				}
				return false;
			}
		}
	}
	void MousePosScript::PlaySceneMouse()
	{
		if (Input::GetKeyDown(eKeyCode::LBUTTON))
		{
			_DotPos = _UnProjectPos;
			GatherObject();

			for (auto Obj : _GameObjects)
			{
				if (Obj->GetComponent<Collider2D>() != nullptr)
					InterSect(Obj->GetComponent<Collider2D>());
			}

			GameObject* Obj = PrimaryObj();

			if (Obj != nullptr)
				Obj->OnClick(_DotPos);
			else
				FeedFood();
		}
		else
		{
			_DotPos = _UnProjectPos;
			GatherObject();

			for (auto Obj : _GameObjects)
			{
				if (Obj->GetComponent<Collider2D>() != nullptr)
					InterSect(Obj->GetComponent<Collider2D>());
			}

			GameObject* Obj = PrimaryObj();

			if (Obj != nullptr)
				Obj->MouseOn();
			else
			{
				for (auto otherObj : _GameObjects)
				{
					if (otherObj->GetName() != L"Coin")
						otherObj->MouseOff();
				}
			}
		}
	}
	void MousePosScript::MenuSceneMouse()
	{
		if (Input::GetKeyDown(eKeyCode::LBUTTON))
		{
			_DotPos = _UnProjectPos;
			GatherObject();

			for (auto Obj : _GameObjects)
			{
				if (Obj->GetComponent<Collider2D>() != nullptr)
					InterSect(Obj->GetComponent<Collider2D>());
			}

			GameObject* Obj = PrimaryObj();

			if (Obj != nullptr)
				Obj->OnClick(_DotPos);
		}
		else
		{
			_DotPos = _UnProjectPos;
			GatherObject();

			for (auto Obj : _GameObjects)
			{
				if (Obj->GetComponent<Collider2D>() != nullptr)
					InterSect(Obj->GetComponent<Collider2D>());
			}

			GameObject* Obj = PrimaryObj();

			if (Obj != nullptr)
				Obj->MouseOn();
			else
			{
				for (auto otherObj : _GameObjects)
				{
						otherObj->MouseOff();
				}
			}
		}
	}
	void MousePosScript::TitleSceneMouse()
	{
		if (Input::GetKeyDown(eKeyCode::LBUTTON))
		{
			_DotPos = _UnProjectPos;
			GatherObject();

			for (auto Obj : _GameObjects)
			{
				if (Obj->GetComponent<Collider2D>() != nullptr)
					InterSect(Obj->GetComponent<Collider2D>());
			}

			GameObject* Obj = PrimaryObj();

			if (Obj != nullptr)
				Obj->OnClick(_DotPos);
		}
		else
		{
			_DotPos = _UnProjectPos;
			GatherObject();

			for (auto Obj : _GameObjects)
			{
				if (Obj->GetComponent<Collider2D>() != nullptr)
					InterSect(Obj->GetComponent<Collider2D>());
			}

			GameObject* Obj = PrimaryObj();

			if (Obj != nullptr)
				Obj->MouseOn();
			else
			{
				for (auto otherObj : _GameObjects)
				{
					otherObj->MouseOff();
				}
			}
		}
	}
}
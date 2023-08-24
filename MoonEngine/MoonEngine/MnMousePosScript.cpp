#include "MnMousePosScript.h"

#include "../Engine_SOURCE/MnApplication.h"
#include "../Engine_SOURCE/MnInput.h"

#include "MnObject.h"
#include "MnGameObject.h"
#include "MnFood.h"
#include "MnInput.h"

extern Mn::Application application;

namespace Mn
{
	MousePosScript::MousePosScript()
		: _Cam(nullptr)
		, _Idx(1)
		, _GameObjects{}
	{
		_Setting.reset();
		_Setting.set((UINT)eLayerType::Coin, 1);
		_Setting.set((UINT)eLayerType::Pet, 1);
		_Setting.set((UINT)eLayerType::Monster, 1);
	}
	MousePosScript::MousePosScript(GameObject* cam)
		: _Cam(cam)
		, _Idx(1)
		, _GameObjects{}
	{
		_Setting.reset();
		_Setting.set((UINT)eLayerType::Coin, 1);
		_Setting.set((UINT)eLayerType::Pet, 1);
		_Setting.set((UINT)eLayerType::Monster, 1);
	}
	MousePosScript::~MousePosScript()
	{
	}
	void MousePosScript::Initialize()
	{

	}
	void MousePosScript::Update()
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
				Obj->Click();
			else
				FeedFood();
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
		if (_UnProjectPos.x > -2.0f && _UnProjectPos.x < 2.0f
			&& _UnProjectPos.y > -1.5f && _UnProjectPos.y < 1.0f)
		{
			float a = (0.0001 * _Idx) + 1;
			Vector3 pos = Vector3(_UnProjectPos.x, _UnProjectPos.y, a);
			Food* food = object::Instantiate<Food>(pos, eLayerType::Food);
			food->Initialize();
			_Idx += 1;
			if (_Idx >= 100)
				_Idx = 1;
		}
	}
}
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
		:_Cam(nullptr)
	{
	}
	MousePosScript::MousePosScript(GameObject* cam)
		:_Cam(cam)
	{
	}
	MousePosScript::~MousePosScript()
	{
	}
	void MousePosScript::Initialize()
	{
	}
	void MousePosScript::Update()
	{
		if (Input::GetKeyDown(eKeyCode::LBUTTON) 
			&& _UnProjectPos.x > -2.0f && _UnProjectPos.x < 2.0f 
			&& _UnProjectPos.y > -1.5f && _UnProjectPos.y < 1.0f )
		{
			int a = 0;
			Vector3 pos = Vector3(_UnProjectPos.x, _UnProjectPos.y, 0);
			Food* food = object::Instantiate<Food>(pos,eLayerType::Food);
			food->Initialize();
		}
	}
	void MousePosScript::LateUpdate()
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
		_UnProjectPos = viewport.Unproject(_WinPos, Camera::GetGpuProjectionMatrix(), Camera::GetGpuViewMatrix(), Matrix::Identity);

		HWND hwnd = application.GetHwnd();
		wchar_t szPos[50] = {};

		//프레임 계산
		swprintf_s(szPos, 50, L"x : %lf, y : %lf", _UnProjectPos.x, _UnProjectPos.y);
		SetWindowText(hwnd, szPos);
	}
	void MousePosScript::Render()
	{
	}
}
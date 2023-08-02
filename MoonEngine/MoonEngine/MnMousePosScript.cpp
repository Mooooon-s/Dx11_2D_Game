#include "MnMousePosScript.h"

#include "../Engine_SOURCE/MnApplication.h"
#include "../Engine_SOURCE/MnInput.h"


extern Mn::Application application;

namespace Mn
{
	MousePosScript::MousePosScript()
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
		Vector3 worldpos;
		Viewport viewport;
		viewport.width = application.GetWidth();
		viewport.height = application.GetHeight();
		viewport.x = 0;
		viewport.y = 0;
		viewport.minDepth = 0.0f;
		viewport.maxDepth = 1.0f;
		worldpos = viewport.Unproject(_WinPos, projection, view, Matrix::Identity);

		HWND hwnd = application.GetHwnd();
		wchar_t szPos[50] = {};

		//프레임 계산
		swprintf_s(szPos, 50, L"x : %lf, y : %lf", worldpos.x, worldpos.y);
		SetWindowText(hwnd, szPos);
	}
	void MousePosScript::Render()
	{
	}
}
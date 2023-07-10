#include "MnGridScript.h"
#include "MnCamera.h"
#include "MnConstantBuffer.h"
#include "MnTransform.h"
#include "MnApplication.h"
#include "MnGameObject.h"
#include "MnRenderer.h"

extern Mn::Application application;

namespace Mn
{
	GridScript::GridScript()
		:_Camera(nullptr)
	{
	}
	GridScript::~GridScript()
	{
	}
	void GridScript::Initialize()
	{
	}
	void GridScript::Update()
	{
		if (_Camera == nullptr)
			return;

		GameObject* gameObj = _Camera->GetOwner();

		Transform* tr = gameObj->GetComponent<Transform>();
		Vector3 pos = tr->Position();

		float scale = _Camera->Size();

		HWND hWnd = application.GetHwnd();
		RECT winRect = {};
		GetClientRect(hWnd, &winRect);

		float width = winRect.right - winRect.left;
		float height = winRect.bottom - winRect.top;
		Vector2 resolution(width, height);

		graphics::ConstantBuffer* cb
			= renderer::constantBuffer[(int)eCBType::Grid];

		renderer::GridCB data;
		data.CameraPosition = Vector4(pos.x, pos.y, pos.z, 1.0f);
		data.Resolution = resolution;
		data.CameraScale = Vector2(scale, scale);

		cb->setData(&data);
		cb->Bind(eShaderStage::VS);
		cb->Bind(eShaderStage::PS);
	}
	void GridScript::LateUpdate()
	{
	}
	void GridScript::Render()
	{
	}
}
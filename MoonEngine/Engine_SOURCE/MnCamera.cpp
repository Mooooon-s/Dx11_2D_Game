#include "MnCamera.h"
#include "MnTransform.h"
#include "MnGameObject.h"
#include "MnApplication.h"
#include "MnRenderer.h"

extern Mn::Application application;

namespace Mn
{
	Matrix Camera::_View = Matrix::Identity;
	Matrix Camera::_Projection = Matrix::Identity;

	Camera::Camera()
		: Component(eComponentType::Camera)
		, _Type(eProjectionType::OrthoGraphic)
		, _AspectRatio(1.0f)
		, _Near(1.0f)
		, _Far(1000.0f)
		, _Size(5.0f)
	{
	}
	Camera::~Camera()
	{
	}
	void Camera::Initialize()
	{
	}
	void Camera::Update()
	{
	}
	void Camera::LateUpdate()
	{
		CreateViewMatrix();
		CreateProjectionMatrix(_Type);
		RegisterCameraInRenderer();
	}
	void Camera::Render()
	{
	}
	bool Camera::CreateViewMatrix()
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector3 pos = tr->Position();

		_View = Matrix::Identity;
		_View *= Matrix::CreateTranslation(-pos);
		
		Vector3 up = tr->Up();
		Vector3 right = tr->Right();
		Vector3 forward = tr->Foward();

		Matrix viewRotation;
		viewRotation._11 = right.x;
		viewRotation._21 = right.y;
		viewRotation._31 = right.z;

		viewRotation._12 = up.x;
		viewRotation._22 = up.y;
		viewRotation._32 = up.z;

		viewRotation._13 = forward.x;
		viewRotation._23 = forward.y;
		viewRotation._33 = forward.z;
		_View *= viewRotation;

		return true;
	}
	bool Camera::CreateProjectionMatrix(eProjectionType type)
	{
		RECT rect = {};
		GetClientRect(application.GetHwnd(), &rect);
		float width = rect.right - rect.left;
		float height = rect.bottom - rect.top;
		_AspectRatio = width / height;

		if (type == eProjectionType::OrthoGraphic)
		{
			float OrthorGraphicRatio = _Size / 1000.0f;
			width *= OrthorGraphicRatio;
			height *= OrthorGraphicRatio;

			_Projection = Matrix::CreateOrthographicLH(width, height, _Near, _Far);
		}
		else
		{
			_Projection = Matrix::CreatePerspectiveFieldOfViewLH(XM_2PI / 6.0f, _AspectRatio, _Near, _Far);
		}

		return true;
	}
	void Camera::RegisterCameraInRenderer()
	{
		renderer::cameras.push_back(this);
	}
	void Camera::TurnLayerMask(eLayerType type, bool enable)
	{
		_LayerMask.set((UINT)type, enable);
	}
	void Camera::SortGameObjects()
	{

	}
	void Camera::RenderOpaque()
	{
		for (GameObject* gameObj : _OpaqueGameObjects)
		{
			if (gameObj == nullptr)
				continue;

			gameObj->Render();
		}
	}
	void Camera::RenderCutOut()
	{
		for (GameObject* gameObj : _CutOutGameObjects)
		{
			if (gameObj == nullptr)
				continue;

			gameObj->Render();
		}
	}
	void Camera::RenderTransparent()
	{
		for (GameObject* gameObj : _TransparentGameObjects)
		{
			if (gameObj == nullptr)
				continue;

			gameObj->Render();
		}
	}
}
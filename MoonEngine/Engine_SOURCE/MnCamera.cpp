#include "MnCamera.h"
#include "MnTransform.h"
#include "MnGameObject.h"
#include "MnApplication.h"
#include "MnRenderer.h"
#include "MnScene.h"
#include "MnSceneManager.h"
#include "MnMeshRenderer.h"

extern Mn::Application application;

namespace Mn
{
	bool CompareZSort(GameObject* a, GameObject* b)
	{
		if (a->GetComponent<Transform>()->Position().z
			<= b->GetComponent<Transform>()->Position().z)
			return false;

		return true;
	}
	Matrix Camera::View = Matrix::Identity;
	Matrix Camera::Projection = Matrix::Identity;

	Camera::Camera()
		: Component(eComponentType::Camera)
		, _Type(eProjectionType::OrthoGraphic)
		, _AspectRatio(1.0f)
		, _Near(1.0f)
		, _Far(1000.0f)
		, _Size(5.0f)
		, _View(Matrix::Identity)
		, _Projection(Matrix::Identity)
	{
		EnableLayerMasks();
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
		View = _View;
		Projection = _Projection;

		AlphaSortGameObjects();
		ZSortTransparencyGameObjects();
		RenderOpaque();
		DisableDepthStencilState();
		RenderCutOut();
		RenderTransparent();
		EnableDepthStencilState();


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
	void Camera::ZSortTransparencyGameObjects()
	{
		std::sort(_CutOutGameObjects.begin(), _CutOutGameObjects.end(), CompareZSort);
		std::sort(_TransparentGameObjects.begin(), _TransparentGameObjects.end(), CompareZSort);
	}
	void Camera::DivideAlphaBlendGameObjects(const std::vector<GameObject*> gameObjs)
	{
		for (GameObject* obj : gameObjs)
		{
			MeshRenderer* mr = obj->GetComponent<MeshRenderer>();
			if (mr == nullptr)
				continue;

			std::shared_ptr<Material> mt = mr->GetMaterial();
			eRenderingMode mode = mt->RenderingMode();
			switch (mode)
			{
			case Mn::graphics::eRenderingMode::Opaque:
				_OpaqueGameObjects.push_back(obj);
				break;
			case Mn::graphics::eRenderingMode::CutOut:
				_CutOutGameObjects.push_back(obj);
				break;
			case Mn::graphics::eRenderingMode::Transparent:
				_TransparentGameObjects.push_back(obj);
				break;
			default:
				break;
			}
		}
	}
	void Camera::AlphaSortGameObjects()
	{
		_OpaqueGameObjects.clear();
		_CutOutGameObjects.clear();
		_TransparentGameObjects.clear();

		//alpha sorting
		Scene* scene = SceneManager::ActiveScene();
		for (int i = 0; i < (UINT)eLayerType::End; i++)
		{
			if(_LayerMask[i] == true)
			{
				Layer& layer = scene->GetLayer((eLayerType)i);
				const std::vector<GameObject*> gameObjs
					= layer.GetGameObjects();


				DivideAlphaBlendGameObjects(gameObjs);
				
			}
		}
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
	void Camera::EnableDepthStencilState()
	{
		Microsoft::WRL::ComPtr<ID3D11DepthStencilState> dsState
			= renderer::depthStencilStates[(UINT)eDSType::Less];
		GetDevice()->BindDepthStencilState(dsState.Get());
	}
	void Camera::DisableDepthStencilState()
	{
		Microsoft::WRL::ComPtr<ID3D11DepthStencilState> dsState
			= renderer::depthStencilStates[(UINT)eDSType::None];
		GetDevice()->BindDepthStencilState(dsState.Get());
	}
}
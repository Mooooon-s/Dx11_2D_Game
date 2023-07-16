#pragma once
#include "MnComponent.h"
#include "MnGraphics.h"

namespace Mn
{
	class Camera : public Component
	{
	public:
		enum class eProjectionType
		{
			Perpective,
			OrthoGraphic,
			None,
		};
	private:
		static Matrix View;
		static Matrix Projection;

		Matrix _View;
		Matrix _Projection;

		eProjectionType _Type;
		float _AspectRatio;
		float _Near;
		float _Far;
		float _Size;

		std::bitset<(UINT)eLayerType::End> _LayerMask;
		std::vector<GameObject*> _OpaqueGameObjects;
		std::vector<GameObject*> _CutOutGameObjects;
		std::vector<GameObject*> _TransparentGameObjects;

	public:
		static Matrix& GetGpuViewMatrix() { return View; }
		static Matrix& GetGpuProjectionMatrix() { return Projection; }
		static void SetGpuViewMatrix(Matrix view) { View = view; }
		static void SetGpuProjectionMatrix(Matrix projection) { Projection = projection; }


	public:
		Camera();
		~Camera();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

	public:



		bool CreateViewMatrix();
		bool CreateProjectionMatrix(eProjectionType type);
		void RegisterCameraInRenderer();

		void TurnLayerMask(eLayerType type, bool enable = true);
		void EnableLayerMasks() { _LayerMask.set(); }
		void DisableLayerMasks() { _LayerMask.reset(); }

		void AlphaSortGameObjects();
		void ZSortTransparencyGameObjects();
		void DivideAlphaBlendGameObjects(const std::vector<GameObject*> gameObjs);

		void RenderOpaque();
		void RenderCutOut();
		void RenderTransparent();

		void EnableDepthStencilState();
		void DisableDepthStencilState();

		float Size() { return _Size; }
		Matrix& GetViewMatrix() { return _View; }
		Matrix& GetProjectionMatrix() { return _Projection; }
	};
}


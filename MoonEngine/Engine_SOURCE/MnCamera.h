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
		static Matrix _View;
		static Matrix _Projection;

		eProjectionType _Type;
		float _AspectRatio;
		float _Near;
		float _Far;
		float _Size;
	public:

		static Matrix GetViewMatrix() { return _View; }
		static Matrix GetProjectionMatrix() { return _Projection; }

		Camera();
		~Camera();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		bool CreateViewMatrix();
		bool CreateProjectionMatrix(eProjectionType type);
	};
}


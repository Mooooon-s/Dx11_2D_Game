#pragma once
#include "MnComponent.h"
#include "MnCamera.h"

namespace Mn
{
	using namespace Mn::graphics;
	class Transform : public Component
	{
	private:
		Vector3 _Position;
		Vector3 _Rotation;
		Vector3 _Scale;

		Vector3 _Up;
		Vector3 _Forward;
		Vector3 _Right;

		Matrix _World;
		Matrix _View;
		Matrix _Projection;
	public:
		Transform();
		~Transform();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		void BindConstantBuffer();

	public:
		void Position(Vector3 position) { _Position = position; }
		void Rotation(Vector3 rotation) { _Rotation = rotation; }
		void Scale(Vector3 scale) { _Scale = scale; }

		void Position(float x, float y, float z) { _Position = Vector3(x, y, z); }
		void Rotation(float x, float y, float z) { _Rotation = Vector3(x, y, z); }
		void Scale(float x, float y, float z) { _Scale = Vector3(x, y, z); }

		Vector3 Position() { return _Position; }
		Vector3 Rotation() { return _Rotation; }
		Vector3 Scale() { return _Scale; }

		Vector3 Foward() { return _Forward; }
		Vector3 Right() { return _Right; }
		Vector3 Up() { return _Up; }
	};
}

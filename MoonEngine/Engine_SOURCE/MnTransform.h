#pragma once
#include "MnComponent.h"

namespace Mn
{
	using namespace Mn::math;
	class Transform : public Component
	{
	private:
		Vector3 _Position;
		Vector3 _Rotation;
		Vector3 _Scale;
	public:
		Transform();
		~Transform();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		void BindConstantBuffer();

		void Position(Vector3 position) { _Position = position; }
		void Rotation(Vector3 rotation) { _Rotation = rotation; }
		void Scale(Vector3 scale) { _Scale = scale; }

		void Position(float x, float y, float z) { _Position = Vector3(x, y, z); }
		void Rotation(float x, float y, float z) { _Rotation = Vector3(x, y, z); }
		void Scale(float x, float y, float z) { _Scale = Vector3(x, y, z); }

		Vector3 Position() { return _Position; }
		Vector3 Rotation() { return _Rotation; }
		Vector3 Scale() { return _Scale; }
	};
}

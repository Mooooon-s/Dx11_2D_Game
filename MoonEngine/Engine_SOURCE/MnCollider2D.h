#pragma once
#include "MnComponent.h"
#include "MnTransform.h"

namespace Mn
{
	class Collider2D : public Component
	{
	private:
		static UINT _Collidernumber;
		static graphics::DebugMesh _DebugMesh;
		UINT _ColliderID;
		eColliderType _Type;
		Transform* _Transform;

		Vector3 _Position;
		Vector2 _Size;
		Vector2 _Center;

		Vector3 _Scale;

		bool _stay;
	public:
		Collider2D();
		~Collider2D();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		void OnCollisionEnter(Collider2D* other);
		void OnCollisionStay(Collider2D* other);
		void OnCollisionExit(Collider2D* other);

		Vector3 HeightVector();
		Vector3 WidthVector();

	public:
		void SetType(eColliderType type) { _Type = type; }
		void SetSize(Vector2 size) { _Size = size; }
		void SetCenter(Vector2 size) { _Center = size; }

		eColliderType GetType() { return _Type; }
		Vector2 GetSize() { return _Size; }
		Vector2 GetCenter() { return _Center; }
		Vector3 GetPosition() { return _Position; }
		Vector3 GetScale() { return _Scale; }
		UINT GetColliderID() { return _ColliderID; }
		graphics::DebugMesh GetDebugMesh() { return _DebugMesh; }
	};

}
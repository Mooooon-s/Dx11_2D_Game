#pragma once
#include "MnComponent.h"
#include "MnTransform.h"

namespace Mn
{
	class Collider2D : public Component
	{
	private:
		static UINT _Collidernumber;
		UINT _ColliderID;
		eColliderType _Type;
		Transform* _Transform;

		Vector3 _Position;
		Vector2 _Size;
		Vector2 _Center;
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

	public:
		void SetType(eColliderType type) { _Type = type; }
		void SetSize(Vector2 size) { _Size = size; }
		void SetCenter(Vector2 size) { _Center = size; }

		UINT GetColliderID() { return _ColliderID; }
	};

}
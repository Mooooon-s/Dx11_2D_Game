#pragma once
#include "MnComponent.h"
#include "MnCollider2D.h"

namespace Mn
{

	class Script : public Component
	{
	private:

	public:
		Script();
		~Script();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		virtual void OnCollisionEnter(Collider2D* other) {};
		virtual void OnCollisionStay(Collider2D* other) {};
		virtual void OnCollisionExit(Collider2D* other) {};

	};

}

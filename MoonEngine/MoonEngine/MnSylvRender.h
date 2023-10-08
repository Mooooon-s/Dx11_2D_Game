#pragma once
#include "MnScript.h"

namespace Mn
{
	class SylvRender : public Script
	{
	public:
		SylvRender();
		~SylvRender();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		virtual void OnCollisionEnter(Collider2D* other) {};
		virtual void OnCollisionStay(Collider2D* other) {};
		virtual void OnCollisionExit(Collider2D* other) {};

	public:
		void AfterTurn();
	private:
	};
}

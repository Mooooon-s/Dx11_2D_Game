#pragma once
#include "MnScript.h"

namespace Mn
{
	class UltravoreRender : public Script
	{
	public:
		UltravoreRender();
		~UltravoreRender();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		virtual void OnCollisionEnter(Collider2D* other) {};
		virtual void OnCollisionStay(Collider2D* other) {};
		virtual void OnCollisionExit(Collider2D* other) {};

	public:
		void afterDeath();
		void afterEat();
	private:
	};
}

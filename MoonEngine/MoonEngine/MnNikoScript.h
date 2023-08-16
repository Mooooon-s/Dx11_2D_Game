#pragma once
#include "MnScript.h"

namespace Mn
{
	class NikoScript : public Script
	{
	public:
		NikoScript();
		~NikoScript();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		virtual void OnCollisionEnter(Collider2D* other) override;
		virtual void OnCollisionStay(Collider2D* other) override;
		virtual void OnCollisionExit(Collider2D* other) override;
	private:
		float _Time;
		bool _Open;
	};
}

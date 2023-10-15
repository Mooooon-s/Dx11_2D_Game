#pragma once
#include "MnScript.h"
namespace Mn
{
	class TailFlopRender : public Script
	{
	public:
		TailFlopRender();
		~TailFlopRender();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;
	private:
		float _Time;
	};
}

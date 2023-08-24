#pragma once
#include "MnScript.h"

namespace Mn
{
	class NikoRenderer : public Script
	{
	public:
		NikoRenderer();
		~NikoRenderer();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;
	public:
		void AfterClick();
	private:
	};
}

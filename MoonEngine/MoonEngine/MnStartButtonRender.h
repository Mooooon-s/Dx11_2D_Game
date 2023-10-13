#pragma once
#include "MnScript.h"
namespace Mn
{
	class StartButtonRender : public Script
	{
	public:
		StartButtonRender();
		~StartButtonRender();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;
	};
}

#pragma once
#include "MnScript.h"
#include "MnConstantBuffer.h"
#include "MnRenderer.h"
#include "MnTime.h"
namespace Mn
{
	class WaterScript : public Script
	{
	private:
		float _Time;
		Vector4 _Times;
	public:
		WaterScript();
		~WaterScript();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;
	public:
		void BindConstantbuffer();
	};
}


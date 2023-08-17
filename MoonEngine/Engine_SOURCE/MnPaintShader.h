#pragma once
#include "MnComputeShader.h"

namespace Mn::graphics
{
	class PaintShader : public ComputeShader
	{
	public:
		virtual void Binds() override;
		virtual void Clear() override;

		void SetTarget(std::shared_ptr<class Texture> target) { _Target = target; }

	private:
		std::shared_ptr<class Texture> _Target;
	};
}

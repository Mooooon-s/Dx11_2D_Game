#pragma once
#include "MnGraphics.h"

namespace Mn::graphics
{
	class ConstantBuffer : public GpuBuffer
	{
	private:
		const eCBType _type;
	public:
		ConstantBuffer(eCBType type);
		~ConstantBuffer();

		bool Create(size_t size);
		void setData(void* data);
		void Bind(eShaderStage stage);
	};
}


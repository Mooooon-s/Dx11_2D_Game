#include "MnConstantBuffer.h"
#include "MnGraphicDevice_Dx11.h"

namespace Mn::graphics
{
	ConstantBuffer::ConstantBuffer(eCBType type)
		: GpuBuffer()
		, _type(type)
	{
	}
	ConstantBuffer::~ConstantBuffer()
	{
	}
	bool ConstantBuffer::Create(size_t size)
	{
		desc.ByteWidth = size;
		desc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_CONSTANT_BUFFER;
		desc.Usage = D3D11_USAGE::D3D11_USAGE_DYNAMIC;
		desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

		Mn::graphics::GetDevice()->CreateBuffer(&desc, nullptr, buffer.GetAddressOf());

		return false;
	}
	void ConstantBuffer::setData(void* data)
	{
		Mn::graphics::GetDevice()->SetConstantBuffer(buffer.Get(), data, desc.ByteWidth);
	}
	void ConstantBuffer::Bind(eShaderStage stage)
	{
		Mn::graphics::GetDevice()->BindConstantBuffer(stage, _type, buffer.Get());
	}
}

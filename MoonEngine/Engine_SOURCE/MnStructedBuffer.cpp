#include "MnStructedBuffer.h"
#include "MnGraphicDevice_Dx11.h"

namespace Mn::graphics
{
	StructedBuffer::StructedBuffer()
		: _SRV(nullptr)
		,_Type(eSRVType::None)
		,_Size(0)
		,_Stride(0)
	{
	}
	StructedBuffer::~StructedBuffer()
	{
	}
	bool StructedBuffer::Create(UINT size, UINT stride, eSRVType type)
	{
		_Size = size;
		_Stride = stride;

		desc.ByteWidth = _Size * _Stride;
		desc.StructureByteStride = _Size;

		desc.Usage = D3D11_USAGE_DYNAMIC;
		desc.CPUAccessFlags = D3D11_CPU_ACCESS_FLAG::D3D11_CPU_ACCESS_WRITE;
		desc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_SHADER_RESOURCE;
		desc.MiscFlags = D3D11_RESOURCE_MISC_FLAG::D3D11_RESOURCE_MISC_BUFFER_STRUCTURED;

		if (!GetDevice()->CreateBuffer(&desc, nullptr, buffer.GetAddressOf()))
			return false;

		D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
		srvDesc.BufferEx.NumElements = _Stride;
		srvDesc.ViewDimension = D3D_SRV_DIMENSION::D3D_SRV_DIMENSION_BUFFEREX;
		
		if (!(GetDevice()->CreateShaderResourceView(buffer.Get(), &srvDesc, _SRV.GetAddressOf())))
			return false;
		
		return true;
	}
	void StructedBuffer::SetData(void* data, UINT stride)
	{
		if (_Stride < stride)
			Create(_Size, stride, eSRVType::None);
		else
			GetDevice()->BindBuffer(buffer.Get(), data, _Size * stride);
	}
	void StructedBuffer::Bind(eShaderStage stage, UINT slot)
	{
		GetDevice()->BindShaderResource(stage, slot, _SRV.GetAddressOf());
	}
}
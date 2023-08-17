#include "MnStructedBuffer.h"
#include "MnGraphicDevice_Dx11.h"

namespace Mn::graphics
{
	StructedBuffer::StructedBuffer()
		: GpuBuffer()
		, _Type(eViewType::SRV)
		, _SRV(nullptr)
		, _Size(0)
		, _Stride(0)
		, _SRVSlot(0)
		, _UAVslot(0)
	{
	}
	StructedBuffer::~StructedBuffer()
	{
	}
	bool StructedBuffer::Create(UINT size, UINT stride, eViewType type, void* data, bool cpuAccess)
	{
		_Type = type;

		_Size = size;
		_Stride = stride;

		desc.ByteWidth = _Size * _Stride;
		desc.StructureByteStride = _Size;

		desc.Usage = D3D11_USAGE::D3D11_USAGE_DEFAULT;
		desc.CPUAccessFlags = 0;
		desc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_SHADER_RESOURCE;
		desc.MiscFlags = D3D11_RESOURCE_MISC_FLAG::D3D11_RESOURCE_MISC_BUFFER_STRUCTURED;

		if (_Type == eViewType::UAV)
		{
			desc.Usage = D3D11_USAGE::D3D11_USAGE_DEFAULT;
			desc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_SHADER_RESOURCE
				| D3D11_BIND_FLAG::D3D11_BIND_UNORDERED_ACCESS;	// Texture Register Binding
			desc.CPUAccessFlags = 0;
		}

		if (data)
		{
			D3D11_SUBRESOURCE_DATA tSub = {};
			tSub.pSysMem = data;

			if (!(GetDevice()->CreateBuffer(&desc, &tSub, buffer.GetAddressOf())))
				return false;
		}
		else
		{
			if (!(GetDevice()->CreateBuffer(&desc, nullptr, buffer.GetAddressOf())))
				return false;
		}

		D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
		srvDesc.BufferEx.NumElements = _Stride;
		srvDesc.ViewDimension = D3D_SRV_DIMENSION::D3D_SRV_DIMENSION_BUFFEREX;
		
		if (!(GetDevice()->CreateShaderResourceView(buffer.Get(), &srvDesc, _SRV.GetAddressOf())))
			return false;
		
		if (_Type == eViewType::UAV)
		{
			D3D11_UNORDERED_ACCESS_VIEW_DESC uavDesc = {};
			uavDesc.Buffer.NumElements = _Stride;
			uavDesc.ViewDimension = D3D11_UAV_DIMENSION_BUFFER;

			if (!GetDevice()->CreateUnordedAccessView(buffer.Get(), &uavDesc, _UAV.GetAddressOf()))
				return false;
		}

		if (cpuAccess)
			CreateRWBuffer();

		return true;
	}
	bool StructedBuffer::CreateRWBuffer()
	{
		D3D11_BUFFER_DESC wDesc(desc);

		wDesc.MiscFlags = D3D11_RESOURCE_MISC_BUFFER_STRUCTURED; // 구조화 버퍼 추가 플래그 설정
		wDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;	// Texture Register Binding	

		wDesc.Usage = D3D11_USAGE_DYNAMIC;
		wDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

		if (!GetDevice()->CreateBuffer( &wDesc, nullptr, _WriteBuffer.GetAddressOf()))
			return false;

		D3D11_BUFFER_DESC rDesc(desc);

		rDesc.MiscFlags = D3D11_RESOURCE_MISC_BUFFER_STRUCTURED; // 구조화 버퍼 추가 플래그 설정
		rDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;	// Texture Register Binding	

		rDesc.Usage = D3D11_USAGE_DEFAULT;
		rDesc.CPUAccessFlags = D3D11_CPU_ACCESS_READ;

		if (!GetDevice()->CreateBuffer(&rDesc, nullptr, _ReadBuffer.GetAddressOf()))
			return false;

		return true;
	}
	void StructedBuffer::SetData(void* data, UINT bufferCount)
	{
		if (_Stride < bufferCount)
			Create(_Size, bufferCount, _Type, data);
		else
			GetDevice()->BindBuffer(_WriteBuffer.Get(), data, _Size * bufferCount);
		GetDevice()->CopyResource(buffer.Get(), _WriteBuffer.Get());
	}
	void StructedBuffer::GetData(void* data, UINT size)
	{
		GetDevice()->CopyResource(_ReadBuffer.Get(), buffer.Get());

		if (size == 0)
			GetDevice()->BindBuffer(_ReadBuffer.Get(), data, _Size * _Stride);
		else
			GetDevice()->BindBuffer(_ReadBuffer.Get(), data, size);
	}
	void StructedBuffer::BindSRV(eShaderStage stage, UINT slot)
	{
		_SRVSlot = slot;
		GetDevice()->BindShaderResource(stage, slot, _SRV.GetAddressOf());
	}
	void StructedBuffer::BindUAV(UINT slot)
	{
		_UAVslot = slot;
		UINT i = -1;
		GetDevice()->BindUnorderedAccess(slot, _UAV.GetAddressOf(), &i);
	}
	void StructedBuffer::Clear()
	{
		// srv clear
		ID3D11ShaderResourceView* srv = nullptr;
		GetDevice()->BindShaderResource(eShaderStage::VS, _SRVSlot, &srv);
		GetDevice()->BindShaderResource(eShaderStage::HS, _SRVSlot, &srv);
		GetDevice()->BindShaderResource(eShaderStage::DS, _SRVSlot, &srv);
		GetDevice()->BindShaderResource(eShaderStage::GS, _SRVSlot, &srv);
		GetDevice()->BindShaderResource(eShaderStage::PS, _SRVSlot, &srv);
		GetDevice()->BindShaderResource(eShaderStage::CS, _SRVSlot, &srv);

		// uav clear
		ID3D11UnorderedAccessView* uav = nullptr;
		UINT i = -1;
		GetDevice()->BindUnorderedAccess(_UAVslot, &uav, &i);
	}
}
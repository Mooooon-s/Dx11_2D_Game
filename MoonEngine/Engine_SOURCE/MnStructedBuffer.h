#pragma once
#include "MnEntity.h"
#include "MnGraphics.h"

namespace Mn::graphics
{

	class StructedBuffer : public GpuBuffer
	{
	public:
		StructedBuffer();
		~StructedBuffer();

	public:
		bool Create(UINT size, UINT stride, eSRVType type);
		void SetData(void* data, UINT stride);
		void Bind(eShaderStage stage, UINT slot);

		UINT GetSize() { return _Size; }
		UINT GetStride() { return _Stride; }
	private:
		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> _SRV;
		eSRVType _Type;

		UINT _Size;
		UINT _Stride;
	};

}
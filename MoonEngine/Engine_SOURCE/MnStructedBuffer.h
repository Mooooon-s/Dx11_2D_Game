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
		bool Create(UINT size, UINT stride, eViewType type,void* data, bool cpuAccess = false);
		bool CreateRWBuffer();
		void SetData(void* data, UINT bufferCount);
		void GetData(void* data, UINT size);
		void BindSRV(eShaderStage stage, UINT slot);
		void BindUAV(UINT slot);

		void Clear();

		UINT GetSize() { return _Size; }
		UINT GetStride() { return _Stride; }
	private:
		Microsoft::WRL::ComPtr<ID3D11Buffer> _ReadBuffer;
		Microsoft::WRL::ComPtr<ID3D11Buffer> _WriteBuffer;

		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> _SRV;
		Microsoft::WRL::ComPtr<ID3D11UnorderedAccessView> _UAV;
		eViewType _Type;

		UINT _Size;
		UINT _Stride;

		UINT _SRVSlot;
		UINT _UAVslot;
	};

}
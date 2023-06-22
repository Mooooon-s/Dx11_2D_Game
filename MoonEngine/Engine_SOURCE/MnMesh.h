#pragma once
#include "MnResource.h"
#include "MnGraphicDevice_Dx11.h"

namespace Mn
{
	using namespace graphics;

	class Mesh : public Resource
	{
	private:
		Microsoft::WRL::ComPtr<ID3D11Buffer> _VertexBuffer;
		Microsoft::WRL::ComPtr<ID3D11Buffer> _IdxBuffer;

		D3D11_BUFFER_DESC _VertexDesc;
		D3D11_BUFFER_DESC _IndexDesc;

		UINT _IndexCount;
	public:
		Mesh();
		~Mesh();
	public:
		virtual HRESULT Load(const std::wstring& path) override;
	public:
		bool CreateVertexBuffer(void* data, UINT Count);
		bool CreateIndexBuffer(void* data, UINT Count);
		void BindBuffer();
		void Render();

		UINT GetIndexCount() { return _IndexCount; }

	};

}

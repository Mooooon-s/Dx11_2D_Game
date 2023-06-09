#pragma once
#include "MoonEngine.h"
#include "MnGraphics.h"

#include <d3d11.h>
#include <d3dcompiler.h>

#pragma comment(lib,"DXGI.lib")
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")

namespace Mn::graphics
{
	class GraphicDevice_Dx11
	{
	private:
		Microsoft::WRL::ComPtr<ID3D11Device> _Device;
		Microsoft::WRL::ComPtr<ID3D11DeviceContext> _Context;
		Microsoft::WRL::ComPtr<ID3D11Texture2D> _RenderTarget;
		Microsoft::WRL::ComPtr<ID3D11RenderTargetView> _RenderTargetView;
		Microsoft::WRL::ComPtr<ID3D11Texture2D> _DepthStencilBuffer;
		Microsoft::WRL::ComPtr<ID3D11DepthStencilView> _DepthStencilView;
		Microsoft::WRL::ComPtr<IDXGISwapChain> _SwapChain;
		CD3D11_VIEWPORT _ViewPort;
	public:
		GraphicDevice_Dx11();
		~GraphicDevice_Dx11();
	public:
		bool CreateSwapChain(const DXGI_SWAP_CHAIN_DESC* desc, HWND hWnd);
		bool CreateTexture(const D3D11_TEXTURE2D_DESC* desc, void* data);
		bool CreateInputLayout(const D3D11_INPUT_ELEMENT_DESC* pInputElementDescs, UINT NumElements, ID3DBlob* byteCode, ID3D11InputLayout** ppInputLayout);
		bool CreateBuffer(D3D11_BUFFER_DESC* desc, D3D11_SUBRESOURCE_DATA* data, ID3D11Buffer** buffer);
		bool CompileFromfile(const std::wstring& fileName, const std::string& funcName, const std::string& version, ID3DBlob** ppCode);
		bool CreateVertexShader(const void* pShaderBytecode, SIZE_T BytecodeLength, ID3D11VertexShader** ppVertexShader);
		bool CreatePixelShader(const void* pShaderBytecode, SIZE_T BytecodeLength, ID3D11PixelShader** ppPixelShader);

		void BindInputLayout(ID3D11InputLayout* pInputlayout);
		void BindPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY Topology);
		void BindVertexBuffer(UINT StartSlot, ID3D11Buffer* const* ppVertexBuffers, const UINT* pStrides, const UINT* pOffsets);
		void BindIndexBuffer(ID3D11Buffer* pIndexBuffer, DXGI_FORMAT Format, UINT Offset);
		void BindVertexShader(ID3D11VertexShader* vs);
		void BindPixelShader(ID3D11PixelShader* ps);
		void SetConstantBuffer(ID3D11Buffer* buffer, void* data, UINT size);
		void BindConstantBuffer(eShaderStage stage, eCBType type, ID3D11Buffer* buffer);
		void BindsConstantBuffer(eShaderStage stage, eCBType type, ID3D11Buffer* buffer);
		
		void BindViewPort(D3D11_VIEWPORT* viewPort);

		void Draw();
		void Present();
	};

	inline GraphicDevice_Dx11*& GetDevice()
	{
		static GraphicDevice_Dx11* device = nullptr;
		return device;
	}
}


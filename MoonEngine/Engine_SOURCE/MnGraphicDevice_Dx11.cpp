#include "MnGraphicDevice_Dx11.h"
#include "MnApplication.h"
#include "MnRenderer.h"

extern Mn::Application application;

namespace Mn::graphics
{
	GraphicDevice_Dx11::GraphicDevice_Dx11()
	{
		//Device, Context »ý¼º
		HWND hWnd = application.GetHwnd();
		UINT deviceFlag = D3D11_CREATE_DEVICE_DEBUG;
		D3D_FEATURE_LEVEL featureLevel = (D3D_FEATURE_LEVEL)0;

		D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr
			, deviceFlag, nullptr, 0
			, D3D11_SDK_VERSION
			, _Device.GetAddressOf(), &featureLevel
			, _Context.GetAddressOf());

		//swapchain(double buffer)
		DXGI_SWAP_CHAIN_DESC swapChainDesc = {};
		swapChainDesc.BufferCount = 2;
		swapChainDesc.BufferDesc.Width = application.GetWidth();
		swapChainDesc.BufferDesc.Height = application.GetHeight();

		if (!CreateSwapChain(&swapChainDesc, hWnd))
			return;

		//get rendertarget by swapchain
		if (FAILED(_SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D)
			, (void**)_RenderTarget.GetAddressOf())))
			return;

		//create rendertarget view
		_Device->CreateRenderTargetView((ID3D11Resource*)_RenderTarget.Get()
			, nullptr,_RenderTargetView.GetAddressOf());
		//depthbuffer
		D3D11_TEXTURE2D_DESC depthStencilDesc = {};
		depthStencilDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_DEPTH_STENCIL;
		depthStencilDesc.Usage = D3D11_USAGE_DEFAULT;
		depthStencilDesc.CPUAccessFlags = 0;

		depthStencilDesc.Format = DXGI_FORMAT::DXGI_FORMAT_D24_UNORM_S8_UINT;
		depthStencilDesc.Width = application.GetWidth();
		depthStencilDesc.Height = application.GetHeight();
		depthStencilDesc.ArraySize = 1;
		
		depthStencilDesc.SampleDesc.Count = 1;
		depthStencilDesc.SampleDesc.Quality = 0;
		
		depthStencilDesc.MiscFlags = 0;
		depthStencilDesc.MipLevels = 0;

		D3D11_SUBRESOURCE_DATA data;
		if (!CreateTexture(&depthStencilDesc, &data))
			return;

		RECT winRect = {};
		GetClientRect(hWnd, &winRect);

		_ViewPort = 
		{	
			0.0f, 0.0f
			, (float)(winRect.right - winRect.left)
			, (float)(winRect.bottom - winRect.top)
			, 0.0f, 1.0f
		};

		BindViewPort(&_ViewPort);
		_Context->OMSetRenderTargets(1, _RenderTargetView.GetAddressOf(), _DepthStencilView.Get());		

	}
	GraphicDevice_Dx11::~GraphicDevice_Dx11()
	{
	}
	bool GraphicDevice_Dx11::CreateSwapChain(const DXGI_SWAP_CHAIN_DESC* desc, HWND hWnd)
	{
		DXGI_SWAP_CHAIN_DESC dxgiDesc = {};

		dxgiDesc.OutputWindow = hWnd;
		dxgiDesc.Windowed = true;
		dxgiDesc.BufferCount = desc->BufferCount;
		dxgiDesc.SwapEffect = DXGI_SWAP_EFFECT::DXGI_SWAP_EFFECT_DISCARD;
		
		dxgiDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		dxgiDesc.BufferDesc.Width = desc->BufferDesc.Width;
		dxgiDesc.BufferDesc.Height = desc->BufferDesc.Height;
		dxgiDesc.BufferDesc.Format = DXGI_FORMAT::DXGI_FORMAT_R8G8B8A8_UNORM;
		dxgiDesc.BufferDesc.RefreshRate.Numerator = 144;
		dxgiDesc.BufferDesc.RefreshRate.Denominator = 1;
		dxgiDesc.BufferDesc.Scaling = DXGI_MODE_SCALING::DXGI_MODE_SCALING_UNSPECIFIED;
		dxgiDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER::DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;

		dxgiDesc.SampleDesc.Count = 1;
		dxgiDesc.SampleDesc.Quality = 0;


		Microsoft::WRL::ComPtr<IDXGIDevice> pDXGIDevice = nullptr;
		Microsoft::WRL::ComPtr<IDXGIAdapter> pAdapter = nullptr;
		Microsoft::WRL::ComPtr<IDXGIFactory> pFactory = nullptr;

		if (FAILED(_Device->QueryInterface(__uuidof(IDXGIDevice), (void**)pDXGIDevice.GetAddressOf())))
			return false;

		if (FAILED(pDXGIDevice->GetParent(__uuidof(IDXGIAdapter), (void**)pAdapter.GetAddressOf())))
			return false;

		if (FAILED(pAdapter->GetParent(__uuidof(IDXGIFactory), (void**)pFactory.GetAddressOf())))
			return false;

		if (FAILED(pFactory->CreateSwapChain(_Device.Get(), &dxgiDesc, _SwapChain.GetAddressOf())))
			return false;

		return true;
	}
	bool GraphicDevice_Dx11::CreateTexture(const D3D11_TEXTURE2D_DESC* desc, void* data)
	{
		D3D11_TEXTURE2D_DESC dxgiDesc = {};
		dxgiDesc.BindFlags = desc->BindFlags;
		dxgiDesc.Usage = desc->Usage;
		dxgiDesc.CPUAccessFlags = 0;
		
		dxgiDesc.Format = desc->Format;
		dxgiDesc.Width = desc->Width;
		dxgiDesc.Height = desc->Height;
		dxgiDesc.ArraySize = desc->ArraySize;

		dxgiDesc.SampleDesc.Count = desc->SampleDesc.Count;
		dxgiDesc.SampleDesc.Quality = 0;

		dxgiDesc.MipLevels = desc->MipLevels;
		dxgiDesc.MiscFlags = desc->MiscFlags;

		if (FAILED(_Device->CreateTexture2D(&dxgiDesc, nullptr, _DepthStencilBuffer.ReleaseAndGetAddressOf())))
			return false;
		if (FAILED(_Device->CreateDepthStencilView(_DepthStencilBuffer.Get(), nullptr, _DepthStencilView.GetAddressOf())))
			return false;

		return true;
	}
	bool GraphicDevice_Dx11::CreateBuffer(D3D11_BUFFER_DESC* desc, D3D11_SUBRESOURCE_DATA* data,ID3D11Buffer** buffer)
	{
		if (FAILED(_Device->CreateBuffer(desc, data, buffer)))
			return false;
		return true;
	}
	bool GraphicDevice_Dx11::CreateShader()
	{
		/* [annotation] */
		//_In_reads_(BytecodeLength)  const void* pShaderBytecode,
		/* [annotation] */
		//_In_  SIZE_T BytecodeLength,
		/* [annotation] */
		//_In_opt_  ID3D11ClassLinkage* pClassLinkage,
		/* [annotation] */
		//_COM_Outptr_opt_  ID3D11VertexShader** ppVertexShader) = 0;
		//ID3DBlob* vsBlob = nullptr;
		std::filesystem::path shaderPath = std::filesystem::current_path().parent_path();
		shaderPath += L"\\Shader_SOURCE\\";

		std::filesystem::path vsPath(shaderPath.c_str());
		vsPath += L"TriangleVS.hlsl";

		D3DCompileFromFile(vsPath.c_str(), nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE
			, "main", "vs_5_0", 0, 0, &Mn::renderer::triangleVSBlob, &Mn::renderer::errorBlob);

		if (Mn::renderer::errorBlob)
		{
			OutputDebugStringA((char*)Mn::renderer::errorBlob->GetBufferPointer());
			Mn::renderer::errorBlob->Release();
		}

		_Device->CreateVertexShader(Mn::renderer::triangleVSBlob->GetBufferPointer()
			, Mn::renderer::triangleVSBlob->GetBufferSize()
			, nullptr, &Mn::renderer::triangleVSShader);

		std::filesystem::path psPath(shaderPath.c_str());
		psPath += L"TrianglePS.hlsl";

		D3DCompileFromFile(psPath.c_str(), nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE
			, "main", "ps_5_0", 0, 0, &Mn::renderer::trianglePSBlob, &Mn::renderer::errorBlob);

		if (Mn::renderer::errorBlob)
		{
			OutputDebugStringA((char*)Mn::renderer::errorBlob->GetBufferPointer());
			Mn::renderer::errorBlob->Release();
		}

		_Device->CreatePixelShader(Mn::renderer::trianglePSBlob->GetBufferPointer()
			, Mn::renderer::trianglePSBlob->GetBufferSize()
			, nullptr, &Mn::renderer::trianglePSShader);

		D3D11_INPUT_ELEMENT_DESC arrLayout[2] = {};
		arrLayout[0].AlignedByteOffset = 0;
		arrLayout[0].Format = DXGI_FORMAT_R32G32B32_FLOAT;
		arrLayout[0].InputSlot = 0;
		arrLayout[0].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		arrLayout[0].SemanticName = "POSITION";
		arrLayout[0].SemanticIndex = 0;

		arrLayout[1].AlignedByteOffset = 12;
		arrLayout[1].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
		arrLayout[1].InputSlot = 0;
		arrLayout[1].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		arrLayout[1].SemanticName = "COLOR";
		arrLayout[1].SemanticIndex = 0;

		_Device->CreateInputLayout(arrLayout, 2
			, renderer::triangleVSBlob->GetBufferPointer()
			, renderer::triangleVSBlob->GetBufferSize()
			, &renderer::triangleLayout);

		return true;
	}
	void GraphicDevice_Dx11::BindViewPort(D3D11_VIEWPORT* viewPort)
	{
		_Context->RSSetViewports(1, viewPort);
	}
	void GraphicDevice_Dx11::Draw()
	{

		FLOAT bgColor[4] = { 0.2f, 0.2f, 0.2f, 1.0f };
		_Context->ClearRenderTargetView(_RenderTargetView.Get(), bgColor);
		_Context->ClearDepthStencilView(_DepthStencilView.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0.0f);


		HWND hWnd = application.GetHwnd();
		RECT winRect = {};
		GetClientRect(hWnd, &winRect);

		_ViewPort = {
			0.0f, 0.0f
			, (float)(winRect.right - winRect.left)
			, (float)(winRect.bottom - winRect.top)
			, 0.0f, 1.0f
		};

		BindViewPort(&_ViewPort);
		_Context->OMSetRenderTargets(1, _RenderTargetView.GetAddressOf(), _DepthStencilView.Get());


		UINT vertexsize = sizeof(renderer::Vertex);
		UINT offset = 0;

		_Context->IASetVertexBuffers(0, 1, &renderer::triangleBuffer, &vertexsize, &offset);
		_Context->IASetInputLayout(renderer::triangleLayout);
		_Context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);


		_Context->VSSetShader(renderer::triangleVSShader, 0, 0);
		_Context->PSSetShader(renderer::trianglePSShader, 0, 0);

		// Draw Render Target
		_Context->Draw(270, 0);

		_SwapChain->Present(0, 0);
	}
}
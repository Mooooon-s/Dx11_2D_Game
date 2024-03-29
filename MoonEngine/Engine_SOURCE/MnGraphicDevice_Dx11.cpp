#include "MnGraphicDevice_Dx11.h"
#include "MnApplication.h"
#include "MnRenderer.h"

extern Mn::Application application;

namespace Mn::graphics
{
	GraphicDevice_Dx11::GraphicDevice_Dx11()
	{
		HWND hWnd = application.GetHwnd();
		UINT deviceFlag = D3D11_CREATE_DEVICE_DEBUG;
		D3D_FEATURE_LEVEL featureLevel = (D3D_FEATURE_LEVEL)0;

		D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr
			, deviceFlag, nullptr, 0
			, D3D11_SDK_VERSION
			, _Device.GetAddressOf(), &featureLevel
			, _Context.GetAddressOf());

		DXGI_SWAP_CHAIN_DESC swapChainDesc = {};
		swapChainDesc.BufferCount = 2;
		swapChainDesc.BufferDesc.Width = application.GetWidth();
		swapChainDesc.BufferDesc.Height = application.GetHeight();

		if (!CreateSwapChain(&swapChainDesc, hWnd))
			return;

		_RenderTarget = std::make_shared<Texture>();
		_DepthStencil = std::make_shared<Texture>();

		Microsoft::WRL::ComPtr<ID3D11Texture2D> renderTarget = nullptr;
		if (FAILED(_SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D)
			, (void**)renderTarget.GetAddressOf())))
			return;
		
		_RenderTarget->SetTexture(renderTarget);

		Microsoft::WRL::ComPtr<ID3D11RenderTargetView> renderTargetView = nullptr;
		_Device->CreateRenderTargetView((ID3D11Resource*)_RenderTarget->GetTexture().Get()
			, nullptr, renderTargetView.GetAddressOf());
		_RenderTarget->SetRTV(renderTargetView);
		
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

		Microsoft::WRL::ComPtr<ID3D11Texture2D> depthStencilBuffer = nullptr;
		if (!CreateTexture2D(&depthStencilDesc, nullptr, depthStencilBuffer.GetAddressOf()))
			return;
		_DepthStencil->SetTexture(depthStencilBuffer);

		Microsoft::WRL::ComPtr<ID3D11DepthStencilView> DepthStencilView = nullptr;
		if (!CraeteDepthStencilView(depthStencilBuffer.Get(), nullptr, DepthStencilView.GetAddressOf()))
			return;
		_DepthStencil->SetDSV(DepthStencilView);

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
		_Context->OMSetRenderTargets(1, _RenderTarget->GetRTV().GetAddressOf(), _DepthStencil->GetDSV().Get());

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
	bool GraphicDevice_Dx11::CreateTexture2D(const D3D11_TEXTURE2D_DESC* desc, void* data, ID3D11Texture2D** ppTexture2D)
	{
		if (FAILED(_Device->CreateTexture2D(desc, nullptr, ppTexture2D)))
			return false;
		return true;
	}
	bool GraphicDevice_Dx11::CreateInputLayout(const D3D11_INPUT_ELEMENT_DESC* pInputElementDescs, UINT NumElements, ID3DBlob* byteCode, ID3D11InputLayout** ppInputLayout)
	{
			if(FAILED(_Device->CreateInputLayout(pInputElementDescs, NumElements
				, byteCode->GetBufferPointer()
				, byteCode->GetBufferSize()
				, ppInputLayout)))
				return false;

			return true;
	}
	bool GraphicDevice_Dx11::CreateBuffer(D3D11_BUFFER_DESC* desc, D3D11_SUBRESOURCE_DATA* data,ID3D11Buffer** buffer)
	{
		if (FAILED(_Device->CreateBuffer(desc, data, buffer)))
			return false;
		return true;
	}
	bool GraphicDevice_Dx11::CompileFromfile(const std::wstring& fileName, const std::string& funcName, const std::string& version, ID3DBlob** ppCode)
	{
		ID3DBlob* errorBlob = nullptr;
		D3DCompileFromFile(fileName.c_str(), nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE
			, funcName.c_str(), version.c_str(), 0, 0, ppCode, &errorBlob);
		if (errorBlob)
		{
			OutputDebugStringA((char*)errorBlob->GetBufferPointer());
			errorBlob->Release();
			errorBlob = nullptr;
		}

		return false;
	}

	bool GraphicDevice_Dx11::CreateVertexShader(const void* pShaderBytecode, SIZE_T BytecodeLength, ID3D11VertexShader** ppVertexShader)
	{
		if(FAILED(_Device->CreateVertexShader(pShaderBytecode, BytecodeLength, nullptr, ppVertexShader)))
			return false;
		return true;
	}

	bool GraphicDevice_Dx11::CreateGeometryShader(const void* pShaderBytecode, SIZE_T BytecodeLength, ID3D11GeometryShader** ppGeometryShader)
	{
		if (FAILED(_Device->CreateGeometryShader(pShaderBytecode, BytecodeLength, nullptr, ppGeometryShader)))
			return false;
		return true;
	}

	bool GraphicDevice_Dx11::CreatePixelShader(const void* pShaderBytecode, SIZE_T BytecodeLength, ID3D11PixelShader** ppPixelShader)
	{
		if(FAILED(_Device->CreatePixelShader(pShaderBytecode, BytecodeLength, nullptr, ppPixelShader)))
			return false;
		return true;
	}
	bool GraphicDevice_Dx11::CreateComputeShader(const void* pShaderBytecode, SIZE_T BytecodeLength, ID3D11ComputeShader** ppComputeShader)
	{
		if (FAILED(_Device->CreateComputeShader(pShaderBytecode, BytecodeLength, nullptr, ppComputeShader)))
			return false;

		return true;
	}
	bool GraphicDevice_Dx11::CreateSamplerState(const D3D11_SAMPLER_DESC* pSamplerDesc, ID3D11SamplerState** ppSamplerState)
	{
		if (FAILED(_Device->CreateSamplerState(pSamplerDesc, ppSamplerState)))
			return false;
		return true;
	}
	bool GraphicDevice_Dx11::CreateRasterizeState(const D3D11_RASTERIZER_DESC* pRasterizerDesc, ID3D11RasterizerState** ppRasterizerState)
	{
		if (FAILED(_Device->CreateRasterizerState(pRasterizerDesc, ppRasterizerState)))
			return false;
		return true;
	}
	bool GraphicDevice_Dx11::CreateDepthStencilState(const D3D11_DEPTH_STENCIL_DESC* pDepthStencilDesc, ID3D11DepthStencilState** ppDepthStencilState)
	{
		if (FAILED(_Device->CreateDepthStencilState(pDepthStencilDesc, ppDepthStencilState)))
			return false;
		return true;
	}
	bool GraphicDevice_Dx11::CreateBlendState(const D3D11_BLEND_DESC* pBlendStateDesc, ID3D11BlendState** ppBlendState)
	{
		if (FAILED(_Device->CreateBlendState(pBlendStateDesc, ppBlendState)))
			return false;
		return true;
	}
	bool GraphicDevice_Dx11::CraeteDepthStencilView(ID3D11Resource* pResource, const D3D11_DEPTH_STENCIL_VIEW_DESC* pDesc, ID3D11DepthStencilView** ppDepthStencilView)
	{
		if (FAILED(_Device->CreateDepthStencilView(pResource, pDesc, ppDepthStencilView)))
			return false;
		return true;
	}
	bool GraphicDevice_Dx11::CreateShaderResourceView(ID3D11Resource* pResource, const D3D11_SHADER_RESOURCE_VIEW_DESC* pDesc, ID3D11ShaderResourceView** ppSRView)
	{
		if (FAILED(_Device->CreateShaderResourceView(pResource, pDesc, ppSRView)))
			return false;
		return true;
	}
	bool GraphicDevice_Dx11::CreateRenderTargetView(ID3D11Resource* pResource, const D3D11_RENDER_TARGET_VIEW_DESC* pDesc, ID3D11RenderTargetView** ppRTView)
	{
		if (FAILED(_Device->CreateRenderTargetView(pResource, pDesc, ppRTView)))
			return false;
		return true;
	}
	bool GraphicDevice_Dx11::CreateUnordedAccessView(ID3D11Resource* pResource, const D3D11_UNORDERED_ACCESS_VIEW_DESC* pDesc, ID3D11UnorderedAccessView** ppUAView)
	{
		if (FAILED(_Device->CreateUnorderedAccessView(pResource, pDesc, ppUAView)))
			return false;
		return true;
	}
	void GraphicDevice_Dx11::BindViewPort(D3D11_VIEWPORT* viewPort)
	{
		_Context->RSSetViewports(1, viewPort);
	}
	void GraphicDevice_Dx11::BindRasterizeState(ID3D11RasterizerState* pRasterizerState)
	{
		_Context->RSSetState(pRasterizerState);
	}
	void GraphicDevice_Dx11::BindDepthStencilState(ID3D11DepthStencilState* pDepthStencilState)
	{
		_Context->OMSetDepthStencilState(pDepthStencilState, 0);
	}

	void GraphicDevice_Dx11::BindBlendState(ID3D11BlendState* pBlendState)
	{
		_Context->OMSetBlendState(pBlendState, nullptr, 0xffffffff);
	}

	void GraphicDevice_Dx11::CopyResource(ID3D11Resource* pDstResource, ID3D11Resource* pSrcResource)
	{
		_Context->CopyResource(pDstResource, pSrcResource);
	}

	void GraphicDevice_Dx11::DrawIndexed(UINT IndexCount, UINT StartIndexLocation, INT BaseVertexLocation)
	{
		_Context->DrawIndexed(IndexCount, StartIndexLocation, BaseVertexLocation);
	}
	void GraphicDevice_Dx11::DrawIndexedInstanced(UINT IndexCountPerInstance, UINT InstanceCount, UINT StartIndexLocation, INT BaseVertexLocation, UINT StartInstanceLocation)
	{
		_Context->DrawIndexedInstanced(IndexCountPerInstance, InstanceCount, StartIndexLocation, BaseVertexLocation, StartInstanceLocation);
	}
	void GraphicDevice_Dx11::BindInputLayout(ID3D11InputLayout* pInputlayout)
	{
		_Context->IASetInputLayout(pInputlayout);
	}
	void GraphicDevice_Dx11::BindPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY Topology)
	{
		_Context->IASetPrimitiveTopology(Topology);
	}
	void GraphicDevice_Dx11::BindVertexBuffer(UINT StartSlot, ID3D11Buffer* const* ppVertexBuffers, const UINT* pStrides, const UINT* pOffsets)
	{
		_Context->IASetVertexBuffers(StartSlot, 1, ppVertexBuffers, pStrides, pOffsets);
	}
	void GraphicDevice_Dx11::BindIndexBuffer(ID3D11Buffer* pIndexBuffer, DXGI_FORMAT Format, UINT Offset)
	{
		_Context->IASetIndexBuffer(pIndexBuffer, Format, Offset);
	}
	void GraphicDevice_Dx11::BindHullShader(ID3D11HullShader* pHullShader)
	{
		_Context->HSSetShader(pHullShader, 0, 0);
	}
	void GraphicDevice_Dx11::BindDomainShader(ID3D11DomainShader* pDomainShader)
	{
		_Context->DSSetShader(pDomainShader, 0, 0);
	}
	void GraphicDevice_Dx11::BindVertexShader(ID3D11VertexShader* vs)
	{
		_Context->VSSetShader(vs, 0, 0);
	}
	void GraphicDevice_Dx11::BindGeometryShader(ID3D11GeometryShader* pGeometryShader)
	{
		_Context->GSSetShader(pGeometryShader, 0, 0);
	}

	void GraphicDevice_Dx11::BindPixelShader(ID3D11PixelShader* ps)
	{
		_Context->PSSetShader(ps, 0, 0);
	}

	void GraphicDevice_Dx11::BindComputeShader(ID3D11ComputeShader* pComputeShader)
	{
		_Context->CSSetShader(pComputeShader, 0, 0);
	}

	void GraphicDevice_Dx11::Dispatch(UINT ThreadGroupCountX, UINT ThreadGroupCountY, UINT ThreadGroupCountZ)
	{
		_Context->Dispatch(ThreadGroupCountX, ThreadGroupCountY, ThreadGroupCountZ);
	}

	void GraphicDevice_Dx11::SetConstantBuffer(ID3D11Buffer* buffer, void* data, UINT size)
	{
		D3D11_MAPPED_SUBRESOURCE subRes = {};
		_Context->Map(buffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &subRes);
		memcpy(subRes.pData, data, size);
		_Context->Unmap(buffer, 0);
	}
	void GraphicDevice_Dx11::BindConstantBuffer(eShaderStage stage, eCBType type, ID3D11Buffer* buffer)
	{
		switch (stage)
		{
		case eShaderStage::VS:
			_Context->VSSetConstantBuffers((UINT)type, 1, &buffer);
			break;
		case eShaderStage::HS:
			_Context->HSSetConstantBuffers((UINT)type, 1, &buffer);
			break;
		case eShaderStage::DS:
			_Context->DSSetConstantBuffers((UINT)type, 1, &buffer);
			break;
		case eShaderStage::GS:
			_Context->GSSetConstantBuffers((UINT)type, 1, &buffer);
			break;
		case eShaderStage::PS:
			_Context->PSSetConstantBuffers((UINT)type, 1, &buffer);
			break;
		case eShaderStage::CS:
			_Context->CSSetConstantBuffers((UINT)type, 1, &buffer);
			break;
		case eShaderStage::End:
			break;
		default:
			break;
		}
	}
	void GraphicDevice_Dx11::BindsConstantBuffer(eShaderStage stage, eCBType type, ID3D11Buffer* buffer)
	{
		_Context->VSSetConstantBuffers((UINT)type, 1, &buffer);
		_Context->HSSetConstantBuffers((UINT)type, 1, &buffer);
		_Context->DSSetConstantBuffers((UINT)type, 1, &buffer);
		_Context->GSSetConstantBuffers((UINT)type, 1, &buffer);
		_Context->PSSetConstantBuffers((UINT)type, 1, &buffer);
		_Context->CSSetConstantBuffers((UINT)type, 1, &buffer);
	}
	void GraphicDevice_Dx11::BindBuffer(ID3D11Buffer* buffer, void* data, UINT size)
	{
		D3D11_MAPPED_SUBRESOURCE sub = {};
		_Context->Map(buffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &sub);
		memcpy(sub.pData, data, size);
		_Context->Unmap(buffer, 0);
	}
	void GraphicDevice_Dx11::BindShaderResource(eShaderStage stage, UINT startSlot, ID3D11ShaderResourceView** ppSRV)
	{
		switch (stage)
		{
		case eShaderStage::VS:
			_Context->VSSetShaderResources(startSlot, 1, ppSRV);
			break;
		case eShaderStage::HS:
			_Context->HSSetShaderResources(startSlot, 1, ppSRV);
			break;
		case eShaderStage::DS:
			_Context->DSSetShaderResources(startSlot, 1, ppSRV);
			break;
		case eShaderStage::GS:
			_Context->GSSetShaderResources(startSlot, 1, ppSRV);
			break;
		case eShaderStage::PS:
			_Context->PSSetShaderResources(startSlot, 1, ppSRV);
			break;
		case eShaderStage::CS:
			_Context->CSSetShaderResources(startSlot, 1, ppSRV);
			break;
		case eShaderStage::End:
			break;
		default:
			break;
		}
	}
	void GraphicDevice_Dx11::BindUnorderedAccess(UINT slot, ID3D11UnorderedAccessView** ppUnorderedAccessViews, const UINT* pUAVInitialCounts)
	{
		_Context->CSSetUnorderedAccessViews(slot, 1, ppUnorderedAccessViews, pUAVInitialCounts);
	}
	void GraphicDevice_Dx11::BindSampler(eShaderStage stage, UINT StartSlot, ID3D11SamplerState** ppSamplers)
	{
		switch (stage)
		{
		case eShaderStage::VS:
			_Context->VSSetSamplers(StartSlot, 1, ppSamplers);
			break;
		case eShaderStage::HS:
			_Context->HSSetSamplers(StartSlot, 1, ppSamplers);
			break;
		case eShaderStage::DS:
			_Context->DSSetSamplers(StartSlot, 1, ppSamplers);
			break;
		case eShaderStage::GS:
			_Context->GSSetSamplers(StartSlot, 1, ppSamplers);
			break;
		case eShaderStage::PS:
			_Context->PSSetSamplers(StartSlot, 1, ppSamplers);
			break;
		case eShaderStage::CS:
			_Context->CSSetSamplers(StartSlot, 1, ppSamplers);
			break;
		case eShaderStage::End:
			break;
		default:
			break;
		}
	}



	
	void GraphicDevice_Dx11::ClearTarget()
	{
		FLOAT bgColor[4] = { 0.2f, 0.2f, 0.2f, 1.0f };
		_Context->ClearRenderTargetView(_RenderTarget->GetRTV().Get(), bgColor);
		_Context->ClearDepthStencilView(_DepthStencil->GetDSV().Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0.0f);
		_Context->OMSetRenderTargets(1, _RenderTarget->GetRTV().GetAddressOf(), _DepthStencil->GetDSV().Get());
	}
	void GraphicDevice_Dx11::UpdateViewPort()
	{
		HWND hWnd = application.GetHwnd();
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
	}
	void GraphicDevice_Dx11::Draw()
	{
	}
	void GraphicDevice_Dx11::Present()
	{
		_SwapChain->Present(0, 0);
	}
}
#include "MnShader.h"
#include "MnRenderer.h"

namespace Mn
{
	Shader::Shader()
		: Resource(Mn::enums::eResourceType::Shader)
		, _InputLayout(nullptr)
		, _Topology(D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST)
		, _RSType(eRSType::SolidBack)
		, _DSType(eDSType::Less)
		, _BSType(eBSType::AlphaBlend)
	{
	}
	Shader::~Shader()
	{
		_InputLayout->Release();
	}
	HRESULT Shader::Load(const std::wstring& path)
	{
		return E_NOTIMPL;
	}
	bool Shader::Create(const eShaderStage stage
		, const std::wstring& fileName
		, const std::string& funcName)
	{
		std::filesystem::path shaderPath 
			= std::filesystem::current_path().parent_path();
		shaderPath += L"\\Shader_SOURCE\\";

		std::filesystem::path fullPath(shaderPath.c_str());
		fullPath += fileName;

		ID3DBlob* errorBlob = nullptr;
		if (stage == eShaderStage::VS)
		{
			GetDevice()->CompileFromfile(fullPath, funcName, "vs_5_0", _VSBlob.GetAddressOf());
			GetDevice()->CreateVertexShader(_VSBlob->GetBufferPointer()
				, _VSBlob->GetBufferSize(),_VS.GetAddressOf());
		}
		else if (stage == eShaderStage::GS)
		{
			GetDevice()->CompileFromfile(fullPath, funcName, "gs_5_0", _GSBlob.GetAddressOf());
			GetDevice()->CreateGeometryShader(_GSBlob->GetBufferPointer()
				, _GSBlob->GetBufferSize(), _GS.GetAddressOf());
		}
		else if (stage == eShaderStage::PS)
		{
			GetDevice()->CompileFromfile(fullPath, funcName, "ps_5_0", _PSBlob.GetAddressOf());
			GetDevice()->CreatePixelShader(_PSBlob->GetBufferPointer()
				, _PSBlob->GetBufferSize(), _PS.GetAddressOf());
		}

		return true;
	}
	void Shader::binds()
	{
		GetDevice()->BindPrimitiveTopology(_Topology);
		GetDevice()->BindInputLayout(_InputLayout);

		GetDevice()->BindVertexShader(_VS.Get());
		GetDevice()->BindGeometryShader(_GS.Get());
		GetDevice()->BindPixelShader(_PS.Get());

		Microsoft::WRL::ComPtr<ID3D11RasterizerState> rsState = renderer::rasterizerStates[(UINT)_RSType];
		Microsoft::WRL::ComPtr<ID3D11DepthStencilState> dsState = renderer::depthStencilStates[(UINT)_DSType];
		Microsoft::WRL::ComPtr<ID3D11BlendState> bsState = renderer::blendStates[(UINT)_BSType];

		GetDevice()->BindRasterizeState(rsState.Get());
		GetDevice()->BindDepthStencilState(dsState.Get());
		GetDevice()->BindBlendState(bsState.Get());

	}
}
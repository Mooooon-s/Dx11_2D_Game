#pragma once
#include "MnResource.h"
#include "MnGraphicDevice_Dx11.h"

namespace Mn
{
	using namespace graphics;
	class Shader : public Resource
	{
	private:
		ID3D11InputLayout* _InputLayout;
		D3D11_PRIMITIVE_TOPOLOGY _Topology;
		Microsoft::WRL::ComPtr < ID3DBlob> _VSBlob;
		Microsoft::WRL::ComPtr < ID3DBlob> _HSBlob;
		Microsoft::WRL::ComPtr < ID3DBlob> _DSBlob;
		Microsoft::WRL::ComPtr < ID3DBlob> _GSBlob;
		Microsoft::WRL::ComPtr < ID3DBlob> _PSBlob;

		Microsoft::WRL::ComPtr < ID3D11VertexShader>	_VS;
		Microsoft::WRL::ComPtr < ID3D11HullShader>		_HS;
		Microsoft::WRL::ComPtr < ID3D11DomainShader>	_DS;
		Microsoft::WRL::ComPtr < ID3D11GeometryShader>	_GS;
		Microsoft::WRL::ComPtr < ID3D11PixelShader>		_PS;


	public:
		Shader();
		~Shader();

		virtual HRESULT Load(const std::wstring& path) override;

		bool Create(const eShaderStage stage, const std::wstring& fileName, const std::string& funcName);
		void binds();
	public:
		ID3DBlob* GetVSCode()
		{
			return _VSBlob.Get();
		}

		ID3D11InputLayout* GetInputLayout()
		{
			return _InputLayout;
		}

		ID3D11InputLayout** GetInputLayoutAddressOf()
		{
			return &_InputLayout;
		}
	};

}

#pragma once
#include "MnResource.h"
#include "MnGraphics.h"

namespace Mn
{
	class ComputeShader : public Resource
	{
	public:
		ComputeShader();
		virtual ~ComputeShader();

		bool Create(const std::wstring& name, const std::string& methodName);
		virtual HRESULT Load(const std::wstring& path) { return S_FALSE; };
	private:
		Microsoft::WRL::ComPtr<ID3DBlob> _CSBlob;
		Microsoft::WRL::ComPtr<ID3D11ComputeShader> _CS;
	};

}
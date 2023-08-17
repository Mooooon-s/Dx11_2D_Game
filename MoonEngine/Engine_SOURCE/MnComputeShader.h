#pragma once
#include "MnResource.h"
#include "MnGraphics.h"

namespace Mn::graphics
{
	class ComputeShader : public Resource
	{
	public:
		ComputeShader(int x,int y,int z);
		ComputeShader();
		virtual ~ComputeShader();

		bool Create(const std::wstring& name, const std::string& methodName);
		virtual HRESULT Load(const std::wstring& path) { return S_FALSE; };
		void OnExcute();

		virtual void Binds();
		virtual void Clear();
	protected:
		Microsoft::WRL::ComPtr<ID3DBlob> _CSBlob;
		Microsoft::WRL::ComPtr<ID3D11ComputeShader> _CS;

		UINT _ThreadGroupCountX;
		UINT _ThreadGroupCountY;
		UINT _ThreadGroupCountZ;

		UINT _GroupX;
		UINT _GroupY;
		UINT _GroupZ;
	};

}
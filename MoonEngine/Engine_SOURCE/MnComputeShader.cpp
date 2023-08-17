#include "MnComputeShader.h"
#include "MnGraphicDevice_Dx11.h"

namespace Mn::graphics
{
	ComputeShader::ComputeShader(int x, int y, int z)
		: Resource(enums::eResourceType::ComputeShader)
	{
		_ThreadGroupCountX = x;
		_ThreadGroupCountY = y;
		_ThreadGroupCountZ = z;
	}
	ComputeShader::ComputeShader()
		:Resource(enums::eResourceType::ComputeShader)
	{
		_ThreadGroupCountX = 32;
		_ThreadGroupCountY = 32;
		_ThreadGroupCountZ = 1;
	}
	ComputeShader::~ComputeShader()
	{
	}
	bool ComputeShader::Create(const std::wstring& name, const std::string& methodName)
	{
		std::filesystem::path shaderPath
			= std::filesystem::current_path().parent_path();
		shaderPath += L"\\Shader_SOURCE\\";

		std::filesystem::path fullPath(shaderPath.c_str());
		fullPath += name;

		ID3DBlob* errorBlob = nullptr;
		graphics::GetDevice()->CompileFromfile(fullPath, methodName, "cs_5_0", _CSBlob.GetAddressOf());
		graphics::GetDevice()->CreateComputeShader(_CSBlob->GetBufferPointer()
			, _CSBlob->GetBufferSize(), _CS.GetAddressOf());
		return true;
	}
	void ComputeShader::OnExcute()
	{
		Binds();
		
		GetDevice()->BindComputeShader(_CS.Get());
		GetDevice()->Dispatch(_GroupX, _GroupY, _GroupZ);

		Clear();
	}
	void ComputeShader::Binds()
	{
	}
	void ComputeShader::Clear()
	{
	}
}
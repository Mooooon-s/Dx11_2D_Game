#include "MnComputeShader.h"
#include "MnGraphicDevice_Dx11.h"

namespace Mn
{
	ComputeShader::ComputeShader()
		:Resource(enums::eResourceType::ComputeShader)
	{
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
}
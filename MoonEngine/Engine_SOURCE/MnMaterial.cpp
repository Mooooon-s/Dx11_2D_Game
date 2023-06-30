#include "MnMaterial.h"
namespace Mn
{
	Material::Material()
		: Resource(Mn::enums::eResourceType::Material)
		, _Shader(nullptr)
		, _Texture(nullptr)
		, _Mode(eRenderingMode::Opaque)
	{
	}
	Material::~Material()
	{
	}
	HRESULT Material::Load(const std::wstring& path)
	{
		return E_NOTIMPL;
	}
	void Material::Binds()
	{
		_Texture->BindShader(eShaderStage::PS, 0);
		_Shader->binds();
	}
	void graphics::Material::Clear()
	{
		_Texture->Clear();
	}
}
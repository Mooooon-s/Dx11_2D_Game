#include "MnMaterial.h"
#include "MnTexture.h"
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
		if (_Texture)
			_Texture->BindShaderResource(eShaderStage::PS, 0);
		if (_TextureAlpha)
			_TextureAlpha->BindShaderResource(eShaderStage::PS, 17);
		if (_Shader)
			_Shader->binds();
	}
	void graphics::Material::TextureBind(std::shared_ptr<Mn::graphics::Texture> tex, int slot)
	{
		tex->BindShaderResource(eShaderStage::PS, slot);
	}
	void graphics::Material::Clear()
	{
		_Texture->Clear();
	}
	Vector2 graphics::Material::CalcurateRatio()
	{
		_Texture->CalculateRatio();
		Vector2 ratio =_Texture->Raitio();
		return ratio;
	}
}
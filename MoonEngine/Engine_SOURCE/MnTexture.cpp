#include "MnTexture.h"
#include "MnGraphicDevice_Dx11.h"

namespace Mn::graphics
{
	Texture::Texture()
		: Resource(Mn::enums::eResourceType::Texture)
		, _Image{}
		, _Texture(nullptr)
		, _SRV(nullptr)
		, _Desc{}
	{
	}
	Texture::~Texture()
	{
	}
	HRESULT Texture::Load(const std::wstring& path)
	{
		wchar_t szExtension[50] = {};
		_wsplitpath_s(path.c_str(), nullptr, 0, nullptr, 0, nullptr, 0, szExtension, 50);

		std::wstring extension = szExtension;
		if (extension == L".dds" || extension == L".DDS")
		{
			if (FAILED(LoadFromDDSFile(path.c_str(), DDS_FLAGS::DDS_FLAGS_NONE, nullptr, _Image)))
				return S_FALSE;
		}
		else if (extension == L".tga" || extension == L".TGA")
		{
			if (FAILED(LoadFromTGAFile(path.c_str(), nullptr, _Image)))
				return S_FALSE;
		}
		else // WIC (png, jpg, jpeg, bmp )
		{
			if (FAILED(LoadFromWICFile(path.c_str(), WIC_FLAGS::WIC_FLAGS_NONE, nullptr, _Image)))
				return S_FALSE;
		}

		CreateShaderResourceView
		(
			GetDevice()->GetID3D11Device()
			, _Image.GetImages()
			, _Image.GetImageCount()
			, _Image.GetMetadata()
			, _SRV.GetAddressOf()
		);
		_SRV->GetResource((ID3D11Resource**)_Texture.GetAddressOf());

		_Width = _Image.GetImages()->width;
		_Height = _Image.GetImages()->height;

		return S_OK;
	}
	void Texture::BindShader(eShaderStage stage, UINT startSlot)
	{
		GetDevice()->BindShaderResource(stage, startSlot, _SRV.GetAddressOf());
	}
	void Texture::Clear()
	{
		ID3D11ShaderResourceView* srv = nullptr;

		GetDevice()->BindShaderResource(eShaderStage::VS,0,&srv);
		GetDevice()->BindShaderResource(eShaderStage::DS,0,&srv);
		GetDevice()->BindShaderResource(eShaderStage::GS,0,&srv);
		GetDevice()->BindShaderResource(eShaderStage::HS,0,&srv);
		GetDevice()->BindShaderResource(eShaderStage::CS,0,&srv);
		GetDevice()->BindShaderResource(eShaderStage::PS,0,&srv);
	}
	void Texture::CalculateRatio()
	{
		if (_Width < _Height)
		{
			_Ratio.x = 1.0f;
			_Ratio.y =  _Width/ _Height;
		}
		else
		{
			_Ratio.x = _Height / _Width;
			_Ratio.y = 1.0f;
		}
	}
}
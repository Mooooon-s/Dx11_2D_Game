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
	bool Texture::Create(UINT width, UINT height, DXGI_FORMAT format, UINT bindFlag)
	{
		if (_Texture == nullptr)
		{
			_Desc.BindFlags = bindFlag;
			_Desc.Usage = D3D11_USAGE_DEFAULT;
			_Desc.CPUAccessFlags = 0;
			_Desc.Format = format;
			_Desc.Width = width;
			_Desc.Height = height;
			_Desc.ArraySize = 1;

			_Desc.SampleDesc.Count = 1;
			_Desc.SampleDesc.Quality = 0;

			_Desc.MipLevels = 0;
			_Desc.MiscFlags = 0;

			mWidth = width;
			mHeight = height;

			if (!GetDevice()->CreateTexture2D(&_Desc, nullptr, _Texture.GetAddressOf()))
				return false;
		}

		if (bindFlag & (UINT)D3D11_BIND_FLAG::D3D11_BIND_DEPTH_STENCIL)
		{
			if (!GetDevice()->CraeteDepthStencilView(_Texture.Get(), nullptr, _DSV.GetAddressOf()))
				return false;
		}
		if (bindFlag & (UINT)D3D11_BIND_FLAG::D3D11_BIND_SHADER_RESOURCE)
		{
			D3D11_SHADER_RESOURCE_VIEW_DESC tSRVDesc = {};
			tSRVDesc.Format = _Desc.Format;
			tSRVDesc.Texture2D.MipLevels = 1;
			tSRVDesc.Texture2D.MostDetailedMip = 0;
			tSRVDesc.ViewDimension = D3D11_SRV_DIMENSION::D3D11_SRV_DIMENSION_TEXTURE2D;

			if (!GetDevice()->CreateShaderResourceView(_Texture.Get(), &tSRVDesc, _SRV.GetAddressOf()))
				return false;
		}

		if (bindFlag & (UINT)D3D11_BIND_FLAG::D3D11_BIND_RENDER_TARGET)
		{
			D3D11_RENDER_TARGET_VIEW_DESC tSRVDesc = {};
			tSRVDesc.Format = _Desc.Format;
			tSRVDesc.Texture2D.MipSlice = 0;
			tSRVDesc.ViewDimension = D3D11_RTV_DIMENSION::D3D11_RTV_DIMENSION_TEXTURE2D;

			if (!GetDevice()->CreateRenderTargetView(_Texture.Get(), nullptr, _RTV.GetAddressOf()))
				return false;
		}

		if (bindFlag & (UINT)D3D11_BIND_FLAG::D3D11_BIND_UNORDERED_ACCESS)
		{
			D3D11_UNORDERED_ACCESS_VIEW_DESC tUAVDesc = {};
			tUAVDesc.Format = _Desc.Format;
			tUAVDesc.Texture2D.MipSlice = 0;
			tUAVDesc.ViewDimension = D3D11_UAV_DIMENSION::D3D11_UAV_DIMENSION_TEXTURE2D;

			if (!GetDevice()->CreateUnordedAccessView(_Texture.Get(), &tUAVDesc, _UAV.GetAddressOf()))
				return false;
		}

		return true;
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
			if (FAILED(LoadFromWICFile(path.c_str(), WIC_FLAGS::WIC_FLAGS_IGNORE_SRGB, nullptr, _Image)))
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

		mWidth = _Image.GetMetadata().width;
		mHeight = _Image.GetMetadata().height;

		return S_OK;
	}
	void Texture::BindShaderResource(eShaderStage stage, UINT startSlot)
	{
		GetDevice()->BindShaderResource(stage, startSlot, _SRV.GetAddressOf());
	}
	void Texture::BindUnorderedAccessViews(UINT slot)
	{
		UINT i = -1;
		GetDevice()->BindUnorderedAccess(slot, _UAV.GetAddressOf(), &i);
	}
	void Texture::ClearUnorderedAccessViews(UINT slot)
	{
		ID3D11UnorderedAccessView* p = nullptr;
		UINT i = -1;
		GetDevice()->BindUnorderedAccess(slot, &p, &i);
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
	math::Vector2 Texture::CalculateRatio()
	{
		if (_Width < _Height)
		{
			_Ratio.x = 1.0f;
			_Ratio.y = _Height/ _Width;
		}
		else
		{
			_Ratio.x = _Width / _Height;
			_Ratio.y = 1.0f;
		}

		return _Ratio;
	}
}
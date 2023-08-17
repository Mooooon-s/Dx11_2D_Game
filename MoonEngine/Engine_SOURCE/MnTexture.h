#pragma once
#include "MnResource.h"
#include "MnGraphics.h"

#include "..\\External\\DirectXTex\\include\\DirectXTex.h"
#include "..\\External\\DirectXTex\\include\\DirectXTex.inl"

#ifdef _DEBUG
#pragma comment(lib,"..\\External\\DirectXTex\\Lib\\Debug\\DirectXTex.lib")
#else
#pragma comment(lib,"..\\External\\DirectXTex\\Lib\\Release\\DirectXTex.lib")
#endif // _DEBUG

namespace Mn::graphics
{
	class Texture : public Resource
	{
	private:
		ScratchImage _Image;
		Microsoft::WRL::ComPtr<ID3D11Texture2D> _Texture;
		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> _SRV;
		Microsoft::WRL::ComPtr<ID3D11RenderTargetView> _RTV;
		Microsoft::WRL::ComPtr<ID3D11DepthStencilView> _DSV;
		Microsoft::WRL::ComPtr<ID3D11UnorderedAccessView> _UAV;

		D3D11_TEXTURE2D_DESC _Desc;

		float _Width;
		float _Height;

		UINT mWidth;
		UINT mHeight;

		math::Vector2 _Ratio;
	public:
		Texture();
		~Texture();

		bool Create(UINT width, UINT height, DXGI_FORMAT format, UINT bindFlag);
		virtual HRESULT Load(const std::wstring& path) override;
		void BindShaderResource(eShaderStage stage, UINT startSlot);
		void BindUnorderedAccessViews(UINT slot);
		void ClearUnorderedAccessViews(UINT slot);
		void Clear();

		math::Vector2 CalculateRatio();
		float GetWidth() { return _Width; }
		float GetHeight() { return _Height; }
		
		size_t GetImageWidth() { return mWidth; }
		size_t GetImageHeight() { return mHeight; }
		math::Vector2 Raitio() { return _Ratio; }

		Microsoft::WRL::ComPtr<ID3D11RenderTargetView>    GetRTV() { return  _RTV; }
		void SetRTV(Microsoft::WRL::ComPtr<ID3D11RenderTargetView> rtv) { _RTV = rtv; }
		Microsoft::WRL::ComPtr<ID3D11DepthStencilView>    GetDSV() { return  _DSV; }
		void SetDSV(Microsoft::WRL::ComPtr<ID3D11DepthStencilView> dsv) { _DSV = dsv; }
		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>  GetSRV() { return  _SRV; }
		Microsoft::WRL::ComPtr<ID3D11UnorderedAccessView> GetUAV() { return  _UAV; }
		Microsoft::WRL::ComPtr<ID3D11Texture2D> GetTexture() { return _Texture; }
		void SetTexture(Microsoft::WRL::ComPtr<ID3D11Texture2D> texture) { _Texture = texture; }


	};
}


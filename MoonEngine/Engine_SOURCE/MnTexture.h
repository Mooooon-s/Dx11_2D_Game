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
		D3D11_TEXTURE2D_DESC _Desc;

		float _Width;
		float _Height;
		math::Vector2 _Ratio;
	public:
		Texture();
		~Texture();

		virtual HRESULT Load(const std::wstring& path) override;
		void BindShader(eShaderStage stage, UINT startSlot);
		void Clear();
		void CalculateRatio();
		float GetWidth() { return _Width; }
		float GetHeight() { return _Height; }
		math::Vector2 Raitio() { return _Ratio; }
	};
}


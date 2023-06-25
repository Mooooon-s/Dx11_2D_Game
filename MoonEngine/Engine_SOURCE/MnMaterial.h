#pragma once
#include "MnResource.h"
#include "MnShader.h"
#include "MnTexture.h"

namespace Mn::graphics
{

	class Material : public Resource
	{
	private:
		std::shared_ptr <Shader> _Shader;
		std::shared_ptr <Texture> _Texture;
	public:
		Material();
		~Material();

		virtual HRESULT Load(const std::wstring& path) override;
		void Binds();

	public:
		void Shader(std::shared_ptr<Shader> shader) { _Shader = shader; }
		void Texture(std::shared_ptr <Texture> mesh) { _Texture = mesh; }

	};

}

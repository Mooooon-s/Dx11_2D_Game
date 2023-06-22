#pragma once
#include "MnResource.h"
#include "MnShader.h"
#include "MnTexture.h"

namespace Mn::graphics
{

	class Material : public Resource
	{
	private:
		Shader* _Shader;
		Texture* _Texture;
	public:
		Material();
		~Material();

		virtual HRESULT Load(const std::wstring& path) override;
		void Binds();

	public:
		void Shader(Shader* shader) { _Shader = shader; }
		void Texture(Texture* mesh) { _Texture = mesh; }

	};

}


#pragma once
#include "MnComponent.h"
#include "MnMesh.h"
#include "MnShader.h"

namespace Mn
{
	class MeshRenderer : public Component
	{
	private:
		Mesh* _Mesh;
		Shader* _Shader;
	public:
		MeshRenderer();
		~MeshRenderer();
	public:
		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;
	};

}

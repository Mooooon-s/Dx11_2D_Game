#pragma once
#include "MoonEngine.h"
#include "MnGraphicDevice_Dx11.h"
#include "MnMesh.h"
#include "MnShader.h"
#include "MnConstantBuffer.h"

using namespace Mn::math;
namespace renderer
{
	struct Vertex
	{
		Vector3 pos;
		Vector4 color;
		Vector2 uv;
	};

	extern Vertex vertices[];
	extern ID3D11InputLayout* triangleLayout;
	extern Mn::Mesh* mesh;
	extern Mn::Shader* shader;
	extern Mn::graphics::ConstantBuffer* constantBuffer;

	void Initialize();
	void Release();

}
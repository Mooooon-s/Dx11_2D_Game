#pragma once
#include "MoonEngine.h"
#include "MnGraphicDevice_Dx11.h"
#include "MnMesh.h"
#include "MnShader.h"
#include "MnConstantBuffer.h"

using namespace Mn::math;
using namespace Mn::graphics;
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
	extern Mn::graphics::ConstantBuffer* constantBuffer[(UINT)eCBType::End];

	void Initialize();
	void Release();

}
#pragma once
#include "MoonEngine.h"
#include "MnGraphicDevice_Dx11.h"
#include "MnMesh.h"
#include "MnShader.h"
#include "MnConstantBuffer.h"
#include "MnCamera.h"

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

	CBUFFER(TransformCB, CBSLOT_TRANSFORM)
	{
		Matrix _World;
		Matrix _View;
		Matrix _Projection;
	};

	CBUFFER(TimeCB, CBSLOT_TIME)
	{
		Vector4 DeltaTime;
	};

	CBUFFER(GridCB, CBSLOT_GRID)
	{
		Vector4 CameraPosition;
		Vector2 CameraScale;
		Vector2 Resolution;
	};

	extern Vertex vertices[];
	extern ID3D11InputLayout* triangleLayout;
	extern Mn::graphics::ConstantBuffer* constantBuffer[(UINT)eCBType::End];
	extern Microsoft::WRL::ComPtr<ID3D11SamplerState> samplerState[];
	extern Microsoft::WRL::ComPtr<ID3D11RasterizerState> rasterizerStates[];
	extern Microsoft::WRL::ComPtr<ID3D11DepthStencilState> depthStencilStates[];
	extern Microsoft::WRL::ComPtr<ID3D11BlendState> blendStates[];

	extern std::vector<Mn::Camera*> cameras;

	void Initialize();
	void Release();
	void Render();

}
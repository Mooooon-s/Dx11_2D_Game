#pragma once
#include "MoonEngine.h"
#include "MnGraphicDevice_Dx11.h"
#include "MnMesh.h"
#include "MnShader.h"
#include "MnConstantBuffer.h"
#include "MnCamera.h"
#include "MnLight.h"

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

	CBUFFER(DebugCB, CBSLOT_DEBUG)
	{
		Vector4 Intersect;
	};

	CBUFFER(AnimatorCB, CBSLOT_ANIMATION)
	{
		Vector2 SpriteleftTop;
		Vector2 SpriteSize;
		Vector2 SpriteOffset;
		Vector2 atlasSize;
		UINT animationType;
	};

	CBUFFER(FlipCB, CBSLOT_FLIPX)
	{
		UINT FlipX;
	};

	CBUFFER(ParticleCB, CBSLOT_PARTICLE)
	{
		UINT elementCount;
		float elpasedTime;
		float deltaTime;
		int padd2;
	};

	CBUFFER(NoiseCB, CBSLOT_NOISE)
	{
		Vector4 size;
	};

	CBUFFER(AlphaCB, CBSLOT_ALPHA)
	{
		float alpha;
	};

	extern Mn::graphics::ConstantBuffer* constantBuffer[(UINT)eCBType::End];
	extern Microsoft::WRL::ComPtr<ID3D11SamplerState> samplerState[];
	extern Microsoft::WRL::ComPtr<ID3D11RasterizerState> rasterizerStates[];
	extern Microsoft::WRL::ComPtr<ID3D11DepthStencilState> depthStencilStates[];
	extern Microsoft::WRL::ComPtr<ID3D11BlendState> blendStates[];

	extern std::multimap<std::wstring, Mn::Light*> Lights;
	extern Mn::Camera* mainCamera;
	extern std::vector<Mn::Camera*> cameras;
	extern std::vector<DebugMesh> debugMeshs;

	void Initialize();
	void BindLights();
	void Release();
	void Render();
	void PushDebugMeshAttribute(DebugMesh mesh);
}
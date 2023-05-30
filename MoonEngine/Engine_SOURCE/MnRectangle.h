#pragma once
#include "MoonEngine.h"
#include "MnGraphicDevice_Dx11.h"

using namespace Mn::math;
namespace Mn::renderer
{
	class Rectangle
	{
	private:
		struct Vertex
		{
			Vector3 pos;
			Vector4 color;
		};
		int buffer;
		Vertex* vertices;
		ID3D11InputLayout* rectangleLayout;
		ID3D11Buffer* rectangleBuffer;
		ID3DBlob* errorBlob;
		ID3DBlob* rectangleVSBlob;
		ID3D11VertexShader* rectangleVSShader;
		ID3DBlob* rectanglePSBlob;
		ID3D11PixelShader* rectanglePSShader;
	public:
		Rectangle();
		~Rectangle();
		void Initialize();
		Vector3 RectPos(int a) { return vertices[a].pos; }
		Vector4 RectColor(int a) { return vertices[a].color; }

	};
}



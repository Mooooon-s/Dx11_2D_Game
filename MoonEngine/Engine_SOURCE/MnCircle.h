#pragma once
#include "MoonEngine.h"
#include "MnGraphicDevice_Dx11.h"
using namespace Mn::math;
namespace Mn::renderer
{
	class Circle
	{
	private:
		struct Vertex
		{
			Vector3 pos;
			Vector4 color;
		};
		int buffer;
		Vertex* vertices;
		Vertex *idxVertices;
	public:
		Circle();
		~Circle();
		void Initialize();
		void Index();
		double Degree2Radian(int degree);
		int BufferSize() { return buffer; }
		Vector3 CirclePos(int a) { return idxVertices[a].pos; }
		Vector4 CircleColor(int a) { return vertices[a].color; }
	};
}


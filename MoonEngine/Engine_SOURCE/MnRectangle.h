#pragma once
#include "MoonEngine.h"
#include "MnGraphicDevice_Dx11.h"

using namespace Mn::math;
namespace Mn
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
	public:
		Rectangle();
		~Rectangle();
		void Initialize();
		Vector3 RectPos(int a) { return vertices[a].pos; }
		Vector4 RectColor(int a) { return vertices[a].color; }

	};
}



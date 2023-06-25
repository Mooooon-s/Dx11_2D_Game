#pragma once
#include "MoonEngine.h"

using namespace Mn::math;
namespace renderer
{
	class Rectangle
	{
	private:
		struct Vertex
		{
			Vector3 pos;
			Vector4 color;
			Vector2 uv;
		};
		Vertex vertices[4];
		std::vector<UINT> idxbuff;
	
	public:
		Rectangle();
		~Rectangle();
		
		void Initialize();
	public:
		Vector3 RectPos(int a) { return vertices[a].pos; }
		Vector4 RectColor(int a) { return vertices[a].color; }
		std::vector<UINT> IndexBuff() { return idxbuff; }

		Vertex* RectVertex() { return vertices; }
	};
}



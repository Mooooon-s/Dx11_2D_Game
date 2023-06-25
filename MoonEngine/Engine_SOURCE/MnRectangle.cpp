#include "MnRectangle.h"

namespace renderer
{
	Rectangle::Rectangle()
		: vertices {}
	{
		idxbuff.resize(6);
	}
	Rectangle::~Rectangle()
	{
	}
	void Rectangle::Initialize()
	{
		vertices[0].pos = Vector3(-1.0f, 1.0f, 0.0f);
		vertices[0].uv = Vector2(0.0f, 0.0f);
		vertices[1].pos = Vector3(1.0f, 1.0f, 0.0f);
		vertices[1].uv = Vector2(1.0f, 0.0f);
		vertices[2].pos = Vector3(1.0f, -1.0f, 0.0f);
		vertices[2].uv = Vector2(1.0f, 1.0f);
		vertices[3].pos = Vector3(-1.0f, -1.0f, 0.0f);
		vertices[3].uv = Vector2(0.0f, 1.0f);

		idxbuff[0]=0;
		idxbuff[1]=1;
		idxbuff[2]=2;
		idxbuff[3]=0;
		idxbuff[4]=2;
		idxbuff[5]=3;
	}
}
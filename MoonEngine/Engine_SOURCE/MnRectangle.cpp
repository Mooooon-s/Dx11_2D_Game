#include "MnRectangle.h"

namespace Mn::renderer
{
	Rectangle::Rectangle()
		:buffer(6)
		,vertices(nullptr)
		,rectangleLayout(nullptr)
		,rectangleBuffer(nullptr)
		,errorBlob(nullptr)
		, rectangleVSBlob(nullptr)
		, rectangleVSShader(nullptr)
		, rectanglePSBlob(nullptr)
		, rectanglePSShader(nullptr)
	{
	}
	Rectangle::~Rectangle()
	{
	}
	void Rectangle::Initialize()
	{
		vertices = new Vertex[buffer];

		vertices[0].pos = Vector3(-1.0f, 1.0f, 0.0f);
		vertices[0].color = Vector4(1.0f, 0.0f, 0.0f,1.0f);

		vertices[1].pos = Vector3(-0.5f, 1.0f, 0.0f);
		vertices[1].color = Vector4(0.0f, 1.0f, 0.0f, 1.0f);

		vertices[2].pos = Vector3(-1.0f, 0.5f, 0.0f);
		vertices[2].color = Vector4(0.0f, 0.0f, 1.0f, 1.0f);

		vertices[3].pos = Vector3(-0.5f, 0.5f, 0.0f);
		vertices[3].color = Vector4(1.0f, 0.0f, 1.0f, 1.0f);

		vertices[4].pos = Vector3(-1.0f, 0.5f, 0.0f);
		vertices[4].color = Vector4(1.0f, 0.0f, 1.0f, 1.0f);

		vertices[5].pos = Vector3(-0.5f, 1.0f, 0.0f);
		vertices[5].color = Vector4(1.0f, 0.0f, 1.0f, 1.0f);
	}
}
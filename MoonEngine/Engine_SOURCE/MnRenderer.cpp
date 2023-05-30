#include "MnRenderer.h"
#include "MnRectangle.h"
#include "MnCircle.h"

#define PI 3.1415926535

namespace Mn::renderer
{
	Vertex vertices[120] = {};
	
	ID3D11InputLayout* triangleLayout = nullptr;
	
	//vertexBuffer
	ID3D11Buffer* triangleBuffer = nullptr;

	//error Blob
	ID3DBlob* errorBlob = nullptr;

	//Vertex shader code == Binary code
	ID3DBlob* triangleVSBlob = nullptr;
	//Vertex shader
	ID3D11VertexShader* triangleVSShader;
	//Pixel shader code == Binary code
	ID3DBlob* trianglePSBlob= nullptr;
	//Pixel Shader
	ID3D11PixelShader* trianglePSShader;

	void SetupState()
	{
		/*D3D11_BUFFER_DESC triangledesc = {};
		triangledesc.ByteWidth = sizeof(Vertex) * 3;
		triangledesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_VERTEX_BUFFER;
		triangledesc.CPUAccessFlags = D3D11_CPU_ACCESS_FLAG::D3D11_CPU_ACCESS_WRITE;
		triangledesc.Usage = D3D11_USAGE::D3D11_USAGE_DYNAMIC;

		D3D11_SUBRESOURCE_DATA triangledata = {};
		triangledata.pSysMem = vertices;
		Mn::graphics::GetDevice()->CreateBuffer(&triangledesc, &triangledata, &triangleBuffer);*/
	}

	void LoadBuffer()
	{
		D3D11_BUFFER_DESC triangleDesc = {};
		triangleDesc.Usage = D3D11_USAGE::D3D11_USAGE_DYNAMIC;
		triangleDesc.ByteWidth = sizeof(Vertex) * 120;
		triangleDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_VERTEX_BUFFER;
		triangleDesc.CPUAccessFlags = D3D11_CPU_ACCESS_FLAG::D3D11_CPU_ACCESS_WRITE;

		D3D11_SUBRESOURCE_DATA triangleData = {};
		triangleData.pSysMem = vertices;
		Mn::graphics::GetDevice()->CreateBuffer( &triangleDesc, &triangleData, &triangleBuffer);
	}

	void LoadShader()
	{
		Mn::graphics::GetDevice()->CreateShader();
	}

	void Initialize()
	{
		Rectangle rectangle;
		rectangle.Initialize();
		Circle circle;
		circle.Initialize();
		vertices[0].pos = Vector3(0.75f, 1.0f, 0.0f);
		vertices[0].color = Vector4(0.0f, 0.0f, 0.0f, 1.0f);

		vertices[1].pos = Vector3(1.0f, 0.5f, 0.0f);
		vertices[1].color = Vector4(0.0f, 0.0f, 0.0f, 1.0f);

		vertices[2].pos = Vector3(0.5f, 0.5f, 0.0f);
		vertices[2].color = Vector4(0.0f, 0.0f, 1.0f, 1.0f);

		for (int i = 3; i < 9; i++)
		{
			vertices[i].pos = rectangle.RectPos(i-3);
			vertices[i].color = rectangle.RectColor(i-3);
		}

		for (int i = 9; i < 96; i++)
		{
			vertices[i].pos = circle.CirclePos(i-9);
			vertices[i].color = circle.CircleColor(i-9);
		}

		vertices[96].pos = Vector3(0.75, 0.0, 0.0);
		vertices[96].color = Vector4(1.0f, 0.0f, 0.0f,1.0f);
		vertices[97].pos = Vector3(1.0, -0.25, 0.0);
		vertices[97].color = Vector4(1.0f, 0.0f, 0.0f,1.0f);
		vertices[98].pos = Vector3(0.5, -0.25, 0.0);
		vertices[98].color = Vector4(1.0f, 0.0f, 0.0f,1.0f);

		vertices[99].pos = Vector3(0.75, -0.5, 0.0f);
		vertices[100].pos = Vector3(0.5, -0.25, 0.0f);
		vertices[101].pos = Vector3(1.0f, -0.25, 0.0f);


		SetupState();
		LoadBuffer();
		LoadShader();
	}
}
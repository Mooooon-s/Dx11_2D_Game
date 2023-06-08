#include "MnRenderer.h"


namespace renderer
{
	using namespace Mn;
	using namespace Mn::graphics;

	Vertex vertices[4] = {};
	Mn::Mesh* mesh = nullptr;
	Mn::Shader* shader = nullptr;
	Mn::graphics::ConstantBuffer* constantBuffer = nullptr;
	
	void SetupState()
	{
		D3D11_INPUT_ELEMENT_DESC arrLayout[2] = {};
		arrLayout[0].AlignedByteOffset = 0;
		arrLayout[0].Format = DXGI_FORMAT_R32G32B32_FLOAT;
		arrLayout[0].InputSlot = 0;
		arrLayout[0].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		arrLayout[0].SemanticName = "POSITION";
		arrLayout[0].SemanticIndex = 0;

		arrLayout[1].AlignedByteOffset = 12;
		arrLayout[1].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
		arrLayout[1].InputSlot = 0;
		arrLayout[1].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		arrLayout[1].SemanticName = "COLOR";
		arrLayout[1].SemanticIndex = 0;

		Mn::graphics::GetDevice()->CreateInputLayout(arrLayout, 2
			,shader->GetVSCode()
			, shader->GetInputLayoutAddressOf());
	}

	void LoadBuffer()
	{
		mesh = new Mn::Mesh();
		mesh->CreateVertexBuffer(vertices, 4);
		//index
		std::vector<UINT> indices = {};
		indices.push_back(0);
		indices.push_back(1);
		indices.push_back(2);

		indices.push_back(0);
		indices.push_back(2);
		indices.push_back(3);
		mesh->CreateIndexBuffer(indices.data(), indices.size());
		
		constantBuffer = new ConstantBuffer(eCBType::Transform);
		constantBuffer->Create(sizeof(Vector4));

		Vector4 _pos = Vector4(0.2f, 0.0f, 0.0f, 1.0f);
		constantBuffer->setData(&_pos);
		constantBuffer->Bind(eShaderStage::VS);
	}

	void LoadShader()
	{
		shader = new Mn::Shader();
		shader->Create(eShaderStage::VS,L"TriangleVS.hlsl","main");
		shader->Create(eShaderStage::PS,L"TrianglePS.hlsl","main");
	}

	void Initialize()
	{
		vertices[0].pos = Vector3(-0.5f, 0.5f, 0.0f);
		vertices[0].color = Vector4(1.0f, 0.0f, 0.0f, 1.0f);

		vertices[1].pos = Vector3(0.5f, 0.5f, 0.0f);
		vertices[1].color = Vector4(0.0f, 1.0f, 0.0f, 1.0f);

		vertices[2].pos = Vector3(0.5f, -0.5f, 0.0f);
		vertices[2].color = Vector4(0.0f, 0.0f, 1.0f, 1.0f);

		vertices[3].pos = Vector3(-0.5f, -0.5f, 0.0f);
		vertices[3].color = Vector4(1.0f, 1.0f, 1.0f, 1.0f);


		LoadBuffer();
		LoadShader();
		SetupState();
	}
	void Release()
	{
		delete mesh;
		delete shader;
		delete constantBuffer;
	}
}
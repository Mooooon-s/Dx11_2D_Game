#include "MnRenderer.h"
#include "MnTexture.h"
#include "MnResources.h"
#include "MnMaterial.h"

namespace renderer
{
	using namespace Mn;
	using namespace Mn::graphics;

	Vertex vertices[4] = {};
	Mn::graphics::ConstantBuffer* constantBuffer[(UINT)eCBType::End] = {};
	Microsoft::WRL::ComPtr<ID3D11SamplerState> samplerState[(UINT)eSamplerType::End] = {};
	
	void SetupState()
	{
		D3D11_INPUT_ELEMENT_DESC arrLayout[3] = {};
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

		arrLayout[2].AlignedByteOffset = 28;
		arrLayout[2].Format = DXGI_FORMAT_R32G32_FLOAT;
		arrLayout[2].InputSlot = 0;
		arrLayout[2].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		arrLayout[2].SemanticName = "TEXCOORD";
		arrLayout[2].SemanticIndex = 0;

		Shader* shader = Mn::Resources::Find<Shader>(L"SpriteShader");
		Mn::graphics::GetDevice()->CreateInputLayout(arrLayout, 3
			,shader->GetVSCode()
			, shader->GetInputLayoutAddressOf());

		D3D11_SAMPLER_DESC desc = {};
		desc.AddressU = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;
		desc.AddressV = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;
		desc.AddressW = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;
		desc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
		GetDevice()->CreateSampler(&desc, samplerState[(UINT)eSamplerType::Point].GetAddressOf());
		GetDevice()->BindSampler(eShaderStage::PS, 0, samplerState[(UINT)eSamplerType::Point].GetAddressOf());

		desc.Filter = D3D11_FILTER_ANISOTROPIC;
		GetDevice()->CreateSampler(&desc, samplerState[(UINT)eSamplerType::Anisotropic].GetAddressOf());
		GetDevice()->BindSampler(eShaderStage::PS, 1, samplerState[(UINT)eSamplerType::Anisotropic].GetAddressOf());
	}

	void LoadBuffer()
	{
		Mesh* mesh = new Mn::Mesh();
		Resources::Insert(L"RectMesh", mesh);
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
		
		constantBuffer[(UINT)eCBType::Transform] = new ConstantBuffer(eCBType::Transform);
		constantBuffer[(UINT)eCBType::Transform]->Create(sizeof(Vector4));

		//Vector4 _pos = Vector4(0.2f, 0.0f, 0.0f, 1.0f);
		//constantBuffer->setData(&_pos);
		//constantBuffer->Bind(eShaderStage::VS);
	}

	void LoadShader()
	{
		Shader* shader = new Mn::Shader();
		shader->Create(eShaderStage::VS,L"SpriteVS.hlsl","main");
		shader->Create(eShaderStage::PS,L"SpritePS.hlsl","main");
		Mn::Resources::Insert(L"SpriteShader", shader);

		Texture* texture = Resources::Load<Texture>(L"m", L"..\\Resources\\Texture\\idle.png");

		Material* spriteMaterial = new Mn::graphics::Material();
		spriteMaterial->Texture(texture);
		spriteMaterial->Shader(shader);
		Mn::Resources::Insert(L"SpriteMaterial", spriteMaterial);
	}

	void Initialize()
	{
		vertices[0].pos = Vector3(-0.5f, 0.5f, 0.0f);
		vertices[0].color = Vector4(1.0f, 0.0f, 0.0f, 1.0f);
		vertices[0].uv = Vector2(0.0f, 0.0f);

		vertices[1].pos = Vector3(0.5f, 0.5f, 0.0f);
		vertices[1].color = Vector4(0.0f, 1.0f, 0.0f, 1.0f);
		vertices[1].uv = Vector2(1.0f, 0.0f);

		vertices[2].pos = Vector3(0.5f, -0.5f, 0.0f);
		vertices[2].color = Vector4(0.0f, 0.0f, 1.0f, 1.0f);
		vertices[2].uv = Vector2(1.0f, 1.0f);

		vertices[3].pos = Vector3(-0.5f, -0.5f, 0.0f);
		vertices[3].color = Vector4(1.0f, 1.0f, 1.0f, 1.0f);
		vertices[3].uv = Vector2(0.0f, 1.0f);


		LoadBuffer();
		LoadShader();
		SetupState();

		Texture* texture = Resources::Load<Texture>(L"m", L"..\\Resources\\Texture\\idle.png");
		texture->BindShader(eShaderStage::PS, 0);
	}
	void Release()
	{
		for (auto cb : constantBuffer)
		{
			if (cb == nullptr)
				continue;

			delete cb;
			cb = nullptr;
		}
		
	}
}
#include "MnRenderer.h"
#include "MnTexture.h"
#include "MnResources.h"
#include "MnMaterial.h"
#include "MnRectangle.h"

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

		std::shared_ptr <Shader> shader = Mn::Resources::Find<Shader>(L"SpriteShader");
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
		std::shared_ptr <Mesh> mesh = std::make_shared<Mesh>();
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

		Rectangle* rect = new Rectangle();
		rect->Initialize();

		std::shared_ptr<Mesh> backgroundMesh = std::make_shared<Mesh>();
		Resources::Insert(L"BackGroundMesh", backgroundMesh);
		backgroundMesh->CreateVertexBuffer(rect->RectVertex(), 4);
		indices = rect->IndexBuff();
		backgroundMesh->CreateIndexBuffer(indices.data(), indices.size());
		
		constantBuffer[(UINT)eCBType::Transform] = new ConstantBuffer(eCBType::Transform);
		constantBuffer[(UINT)eCBType::Transform]->Create(sizeof(TransformCB));
	}

	void LoadShader()
	{
		//--------------------------------------------------------------------------------------------------------------------------------------
		//							
		//																Shader
		// 
		//--------------------------------------------------------------------------------------------------------------------------------------
		std::shared_ptr <Shader> shader = std::make_shared<Shader>();
		shader->Create(eShaderStage::VS, L"SpriteVS.hlsl", "main");
		shader->Create(eShaderStage::PS, L"SpritePS.hlsl", "main");
		Mn::Resources::Insert(L"SpriteShader", shader);

		//---------------------------------------------------------------------------------------------------------------------------------------
		//
		//																Player
		//
		//---------------------------------------------------------------------------------------------------------------------------------------
		// 
		//----------------------------------------------------------------
		//							Texture
		//----------------------------------------------------------------
		std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"player", L"..\\Resources\\Texture\\idle.png");

		//----------------------------------------------------------------
		//							Material
		//----------------------------------------------------------------
		std::shared_ptr <Material> spriteMaterial = std::make_shared<Material>();
		spriteMaterial->Texture(texture);
		spriteMaterial->Shader(shader);
		Mn::Resources::Insert(L"SpriteMaterial", spriteMaterial);

		//---------------------------------------------------------------------------------------------------------------------------------------
		//
		//																BackGround
		//
		//---------------------------------------------------------------------------------------------------------------------------------------
		// 
		//----------------------------------------------------------------
		//							Texture
		//----------------------------------------------------------------
		std::shared_ptr<Texture> backgroundTex[3];
		backgroundTex[0] = Resources::Load<Texture>(L"BackGround_", L"..\\Resources\\Texture\\BackGround\\background_layer_1.png");
		//----------------------------------------------------------------
		//							Material
		//----------------------------------------------------------------
		std::shared_ptr<Material> backgroundMaterial = std::make_shared<Material>();
		backgroundMaterial->Texture(backgroundTex[0]);
		backgroundMaterial->Shader(shader);
		Mn::Resources::Insert(L"BackGroundMaterial_Layer_0", backgroundMaterial);

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

		std::shared_ptr <Texture> texture = Resources::Load<Texture>(L"player", L"..\\Resources\\Texture\\idle.png");
		texture = Resources::Load<Texture>(L"BackGround", L"..\\Resources\\Texture\\BackGround\\background_layer_1.png");
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
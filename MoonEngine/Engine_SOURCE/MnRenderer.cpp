#include "MnRenderer.h"
#include "MnTexture.h"
#include "MnResources.h"
#include "MnMaterial.h"
#include "MnRectangle.h"
#include "MnTime.h"

namespace renderer
{
	using namespace Mn;
	using namespace Mn::graphics;

	Vertex vertices[4] = {};
	Mn::graphics::ConstantBuffer* constantBuffer[(UINT)eCBType::End] = {};
	Microsoft::WRL::ComPtr<ID3D11SamplerState> samplerState[(UINT)eSamplerType::End] = {};
	Microsoft::WRL::ComPtr<ID3D11RasterizerState> rasterizerStates[(UINT)eRSType::End] = {};
	Microsoft::WRL::ComPtr<ID3D11DepthStencilState> depthStencilStates[(UINT)eDSType::End] = {};
	Microsoft::WRL::ComPtr<ID3D11BlendState> blendStates[(UINT)eBSType::End] = {};

	std::vector<Mn::Camera*> cameras = {};
	
	void SetupState()
	{
#pragma region InputLayout
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

		std::shared_ptr <Shader> watershader = Mn::Resources::Find<Shader>(L"WaterShader");
		Mn::graphics::GetDevice()->CreateInputLayout(arrLayout, 3
			, watershader->GetVSCode()
			, watershader->GetInputLayoutAddressOf());

		std::shared_ptr <Shader> HPshader = Mn::Resources::Find<Shader>(L"HPShader");
		Mn::graphics::GetDevice()->CreateInputLayout(arrLayout, 3
			, HPshader->GetVSCode()
			, HPshader->GetInputLayoutAddressOf());

		std::shared_ptr <Shader> BGshader = Mn::Resources::Find<Shader>(L"BGShader");
		Mn::graphics::GetDevice()->CreateInputLayout(arrLayout, 3
			, BGshader->GetVSCode()
			, BGshader->GetInputLayoutAddressOf());

		std::shared_ptr <Shader> GridShader = Mn::Resources::Find<Shader>(L"GridShader");
		Mn::graphics::GetDevice()->CreateInputLayout(arrLayout, 3
			, GridShader->GetVSCode()
			, GridShader->GetInputLayoutAddressOf());

		std::shared_ptr <Shader> MonShader = Mn::Resources::Find<Shader>(L"MonsterShader");
		Mn::graphics::GetDevice()->CreateInputLayout(arrLayout, 3
			, MonShader->GetVSCode()
			, MonShader->GetInputLayoutAddressOf());

#pragma endregion
#pragma region SamplerState
		D3D11_SAMPLER_DESC Samplerdesc = {};
		Samplerdesc.AddressU = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;
		Samplerdesc.AddressV = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;
		Samplerdesc.AddressW = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;
		Samplerdesc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
		GetDevice()->CreateSamplerState(&Samplerdesc, samplerState[(UINT)eSamplerType::Point].GetAddressOf());
		GetDevice()->BindSampler(eShaderStage::PS, 0, samplerState[(UINT)eSamplerType::Point].GetAddressOf());

		Samplerdesc.Filter = D3D11_FILTER_ANISOTROPIC;
		GetDevice()->CreateSamplerState(&Samplerdesc, samplerState[(UINT)eSamplerType::Anisotropic].GetAddressOf());
		GetDevice()->BindSampler(eShaderStage::PS, 1, samplerState[(UINT)eSamplerType::Anisotropic].GetAddressOf());
#pragma endregion
#pragma region Rasterizer State
		D3D11_RASTERIZER_DESC rasterizerDesc = {};
		rasterizerDesc.FillMode = D3D11_FILL_MODE::D3D11_FILL_SOLID;
		rasterizerDesc.CullMode = D3D11_CULL_MODE::D3D11_CULL_BACK;
		GetDevice()->CreateRasterizeState(&rasterizerDesc, rasterizerStates[(UINT)eRSType::SolidBack].GetAddressOf());

		rasterizerDesc.FillMode = D3D11_FILL_MODE::D3D11_FILL_SOLID;
		rasterizerDesc.CullMode = D3D11_CULL_MODE::D3D11_CULL_FRONT;
		GetDevice()->CreateRasterizeState(&rasterizerDesc, rasterizerStates[(UINT)eRSType::SolidFront].GetAddressOf());

		rasterizerDesc.FillMode = D3D11_FILL_MODE::D3D11_FILL_SOLID;
		rasterizerDesc.CullMode = D3D11_CULL_MODE::D3D11_CULL_NONE;
		GetDevice()->CreateRasterizeState(&rasterizerDesc, rasterizerStates[(UINT)eRSType::SolidNone].GetAddressOf());
#pragma endregion
#pragma region DepthStencil State
		D3D11_DEPTH_STENCIL_DESC depthStencilDesc = {};

		//less
		depthStencilDesc.DepthEnable = true;
		depthStencilDesc.DepthFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_LESS;
		depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
		depthStencilDesc.StencilEnable = false;

		GetDevice()->CreateDepthStencilState(&depthStencilDesc
			, depthStencilStates[(UINT)eDSType::Less].GetAddressOf());

		//Greater
		depthStencilDesc.DepthEnable = true;
		depthStencilDesc.DepthFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_GREATER;
		depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
		depthStencilDesc.StencilEnable = false;

		GetDevice()->CreateDepthStencilState(&depthStencilDesc
			, depthStencilStates[(UINT)eDSType::Greater].GetAddressOf());

		//No Write
		depthStencilDesc.DepthEnable = true;
		depthStencilDesc.DepthFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_LESS;
		depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO;
		depthStencilDesc.StencilEnable = false;

		GetDevice()->CreateDepthStencilState(&depthStencilDesc
			, depthStencilStates[(UINT)eDSType::NoWrite].GetAddressOf());

		//None
		depthStencilDesc.DepthEnable = false;
		depthStencilDesc.DepthFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_LESS;
		depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO;
		depthStencilDesc.StencilEnable = false;

		GetDevice()->CreateDepthStencilState(&depthStencilDesc
			, depthStencilStates[(UINT)eDSType::None].GetAddressOf());
#pragma endregion
#pragma region Blend State
		D3D11_BLEND_DESC blendDesc = {};
		//default
		blendStates[(UINT)eBSType::Default] = nullptr;
		// Alpha Blend
		blendDesc.AlphaToCoverageEnable = false;
		blendDesc.IndependentBlendEnable = false;
		blendDesc.RenderTarget[0].BlendEnable = true;
		blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP::D3D11_BLEND_OP_ADD;
		blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
		blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
		blendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP::D3D11_BLEND_OP_ADD;
		blendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
		blendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
		blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

		GetDevice()->CreateBlendState(&blendDesc, blendStates[(UINT)eBSType::AlphaBlend].GetAddressOf());

		// one one
		blendDesc.AlphaToCoverageEnable = false;
		blendDesc.IndependentBlendEnable = false;
		blendDesc.RenderTarget[0].BlendEnable = true;
		blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP::D3D11_BLEND_OP_ADD;
		blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_ONE;
		blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_ONE;
		blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

		GetDevice()->CreateBlendState(&blendDesc, blendStates[(UINT)eBSType::OneOne].GetAddressOf());


#pragma endregion
	}

	void LoadMesh()
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

		constantBuffer[(UINT)eCBType::Time] = new ConstantBuffer(eCBType::Time);
		constantBuffer[(UINT)eCBType::Time]->Create(sizeof(TimeCB));

		constantBuffer[(UINT)eCBType::Grid] = new ConstantBuffer(eCBType::Grid);
		constantBuffer[(UINT)eCBType::Grid]->Create(sizeof(GridCB));
	}

	void LoadShader()
	{
		//--------------------------------------------------------------------------------------------------------------------------------------
		//							
		//																Shader
		// 
		//--------------------------------------------------------------------------------------------------------------------------------------
		
		//sprite
		std::shared_ptr <Shader> shader = std::make_shared<Shader>();
		shader->Create(eShaderStage::VS, L"SpriteVS.hlsl", "main");
		shader->Create(eShaderStage::PS, L"SpritePS.hlsl", "main");
		Mn::Resources::Insert(L"SpriteShader", shader);

		//water
		std::shared_ptr<Shader> watershader = std::make_shared<Shader>();
		watershader->Create(eShaderStage::VS, L"WaterVS.hlsl", "main");
		watershader->Create(eShaderStage::PS, L"WaterPS.hlsl", "main");
		Mn::Resources::Insert(L"WaterShader", watershader);

		//BackGorund
		std::shared_ptr<Shader> BGshader = std::make_shared<Shader>();
		BGshader->Create(eShaderStage::VS, L"BGVS.hlsl", "main");
		BGshader->Create(eShaderStage::PS, L"BGPS.hlsl", "main");
		Mn::Resources::Insert(L"BGShader", BGshader);

		//GUI_HP
		std::shared_ptr<Shader> HPshader = std::make_shared<Shader>();
		HPshader->Create(eShaderStage::VS, L"HPVS.hlsl", "main");
		HPshader->Create(eShaderStage::PS, L"HPPS.hlsl", "main");
		Mn::Resources::Insert(L"HPShader", HPshader);

		std::shared_ptr<Shader> girdShader = std::make_shared<Shader>();
		girdShader->Create(eShaderStage::VS, L"GridVS.hlsl", "main");
		girdShader->Create(eShaderStage::PS, L"GridPS.hlsl", "main");
		Mn::Resources::Insert(L"GridShader", girdShader);

		std::shared_ptr<Shader> MonShader = std::make_shared<Shader>();
		MonShader->Create(eShaderStage::VS, L"MonsterVS.hlsl", "main");
		MonShader->Create(eShaderStage::PS, L"MonsterPS.hlsl", "main");
		Mn::Resources::Insert(L"MonsterShader", MonShader);

	}

	void LoadMaterial()
	{
		//---------------------------------------------------------------------------------------------------------------------------------------
		//
		//																Player
		//
		//---------------------------------------------------------------------------------------------------------------------------------------
		// ---------------------------------------------------------------
		//							Shader
		// ---------------------------------------------------------------
		std::shared_ptr<Shader> spriteShader
			= Resources::Find<Shader>(L"SpriteShader");
		// 
		//----------------------------------------------------------------
		//							Texture
		//----------------------------------------------------------------
		std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"player", L"..\\Resources\\Texture\\idle.png");

		//----------------------------------------------------------------
		//							Material
		//----------------------------------------------------------------
		std::shared_ptr <Material> spriteMaterial = std::make_shared<Material>();
		spriteMaterial->SetTexture(texture);
		spriteMaterial->Shader(spriteShader);
		spriteMaterial->RenderingMode(eRenderingMode::Transparent);
		Mn::Resources::Insert(L"SpriteMaterial", spriteMaterial);


		//---------------------------------------------------------------------------------------------------------------------------------------
		//
		//																Monster
		//
		//---------------------------------------------------------------------------------------------------------------------------------------
		// ---------------------------------------------------------------
		//							Shader
		// ---------------------------------------------------------------
		std::shared_ptr<Shader> MonShader
			= Resources::Find<Shader>(L"MonsterShader");
		// 
		//----------------------------------------------------------------
		//							Texture
		//----------------------------------------------------------------
		std::shared_ptr<Texture> Montexture = Resources::Load<Texture>(L"Monster_Pumpkin", L"..\\Resources\\Texture\\Monster\\Undead_pumpking_Sprites.png");

		//----------------------------------------------------------------
		//							Material
		//----------------------------------------------------------------
		std::shared_ptr <Material> MonMaterial = std::make_shared<Material>();
		MonMaterial->SetTexture(Montexture);
		MonMaterial->Shader(MonShader);
		MonMaterial->RenderingMode(eRenderingMode::Transparent);
		Mn::Resources::Insert(L"MonMaterial", MonMaterial);

		//---------------------------------------------------------------------------------------------------------------------------------------
		//
		//																BackGround
		//
		//---------------------------------------------------------------------------------------------------------------------------------------
		// 
		// ---------------------------------------------------------------
		//							Shader
		// ---------------------------------------------------------------
		std::shared_ptr<Shader>  backgroundShader
			= Resources::Find<Shader>(L"BGShader");

		std::shared_ptr<Shader>  WaterShader
			= Resources::Find<Shader>(L"WaterShader");
		//----------------------------------------------------------------
		//							Texture
		//----------------------------------------------------------------
		std::shared_ptr<Texture> backgroundTex[3];
		backgroundTex[0] = Resources::Load<Texture>(L"BackGround_forest_sky", L"..\\Resources\\Texture\\BackGround\\background_stage_1_sky.png");
		backgroundTex[1] = Resources::Load<Texture>(L"BackGround_forest_tree", L"..\\Resources\\Texture\\BackGround\\background_stage_1_tree.png");
		//----------------------------------------------------------------
		//							Material
		//----------------------------------------------------------------
		std::shared_ptr<Material> backgroundMaterial = std::make_shared<Material>();
		backgroundMaterial->SetTexture(backgroundTex[0]);
		backgroundMaterial->Shader(backgroundShader);
		backgroundMaterial->RenderingMode(eRenderingMode::Opaque);
		Mn::Resources::Insert(L"BackGroundMaterial_Layer_0", backgroundMaterial);

		std::shared_ptr<Material> backgroundMaterial2 = std::make_shared<Material>();
		backgroundMaterial2->SetTexture(backgroundTex[1]);
		backgroundMaterial2->Shader(backgroundShader);
		backgroundMaterial->RenderingMode(eRenderingMode::Transparent);
		Mn::Resources::Insert(L"BackGroundMaterial_Layer_1", backgroundMaterial2);


		//Water
		std::shared_ptr<Texture> WaterTex;
		WaterTex = Resources::Load<Texture>(L"Water_Bump", L"..\\Resources\\Texture\\Water\\Water_Bump.png");
		std::shared_ptr<Material> WaterMat = std::make_shared<Material>();
		WaterMat->SetTexture(WaterTex);
		WaterMat->TextureBind(backgroundTex[0], 1);
		WaterMat->Shader(WaterShader);
		WaterMat->RenderingMode(eRenderingMode::Transparent);
		Mn::Resources::Insert(L"WaterMaterial", WaterMat);

		//---------------------------------------------------------------------------------------------------------------------------------------
		//
		//																GUI
		//
		//---------------------------------------------------------------------------------------------------------------------------------------
		// ---------------------------------------------------------------
		//							Shader
		// ---------------------------------------------------------------
		std::shared_ptr<Shader>  HPShader
			= Resources::Find<Shader>(L"HPShader");
		
		//----------------------------------------------------------------
		//							Texture
		//----------------------------------------------------------------

		//HP
		std::shared_ptr<Texture> Hpbar = std::make_shared<Texture>();
		std::shared_ptr<Texture> HpbarBack = std::make_shared<Texture>();
		std::shared_ptr<Texture> HpbarFrame = std::make_shared<Texture>();
		Hpbar = Resources::Load<Texture>(L"HP_BAR_", L"..\\Resources\\Texture\\GUI\\HP_BAR\\BarV7_ProgressBar.png");
		HpbarBack = Resources::Load<Texture>(L"HP_BAR_Back", L"..\\Resources\\Texture\\GUI\\HP_BAR\\BarV7_Bar.png");
		HpbarFrame = Resources::Load<Texture>(L"HP_BAR_FRAME", L"..\\Resources\\Texture\\GUI\\HP_BAR\\BarV7_ProgressBarBorder.png");

		//----------------------------------------------------------------
		//							Material
		//----------------------------------------------------------------

		//Hp
		std::shared_ptr<Material> HpMat = std::make_shared<Material>();
		HpMat->SetTexture(Hpbar);
		HpMat->Shader(HPShader);
		HpMat->RenderingMode(eRenderingMode::Opaque);
		Resources::Insert<Material>(L"Hp_Bar", HpMat);


		//---------------------------------------------------------------------------------------------------------------------------------------
		//
		//																Grid
		//
		//---------------------------------------------------------------------------------------------------------------------------------------
		// ---------------------------------------------------------------
		//							Shader
		// ---------------------------------------------------------------
		std::shared_ptr<Shader> gridShader
			= Resources::Find<Shader>(L"GridShader");

		std::shared_ptr<Material> material = std::make_shared<Material>();
		//material->SetTexture(Hpbar);
		material->Shader(gridShader);
		Resources::Insert(L"GridMaterial", material);
	}


	void Initialize()
	{
		LoadMesh();
		LoadBuffer();
		LoadShader();
		SetupState();
		LoadMaterial();
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
	void Render()
	{
		for (Camera* cam : cameras)
		{
			if (cam == nullptr)
				continue;

			cam->Render();
		}

		cameras.clear();
	}
}
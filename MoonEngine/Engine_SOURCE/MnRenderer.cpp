#include "MnRenderer.h"
#include "MnTexture.h"
#include "MnResources.h"
#include "MnMaterial.h"
#include "MnTime.h"

namespace renderer
{
	using namespace Mn;
	using namespace Mn::graphics;

	Mn::graphics::ConstantBuffer* constantBuffer[(UINT)eCBType::End] = {};
	Microsoft::WRL::ComPtr<ID3D11SamplerState> samplerState[(UINT)eSamplerType::End] = {};
	
	Microsoft::WRL::ComPtr<ID3D11RasterizerState> rasterizerStates[(UINT)eRSType::End] = {};
	Microsoft::WRL::ComPtr<ID3D11DepthStencilState> depthStencilStates[(UINT)eDSType::End] = {};
	Microsoft::WRL::ComPtr<ID3D11BlendState> blendStates[(UINT)eBSType::End] = {};

	Mn::Camera* mainCamera = nullptr;
	std::vector<Mn::Camera*> cameras = {};
	std::vector<DebugMesh> debugMeshs = {};
	
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

		std::shared_ptr <Shader> DebugShader = Mn::Resources::Find<Shader>(L"DebugShader");
		Mn::graphics::GetDevice()->CreateInputLayout(arrLayout, 3
			, DebugShader->GetVSCode()
			, DebugShader->GetInputLayoutAddressOf());


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
		std::vector<Vertex> vertices = {};
		std::vector<UINT> indices = {};


		vertices.resize(4);
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

		std::shared_ptr <Mesh> mesh = std::make_shared<Mesh>();
		Resources::Insert(L"RectMesh", mesh);
		mesh->CreateVertexBuffer(vertices.data(), vertices.size());
		//index
		indices.push_back(0);
		indices.push_back(1);
		indices.push_back(2);

		indices.push_back(0);
		indices.push_back(2);
		indices.push_back(3);
		mesh->CreateIndexBuffer(indices.data(), indices.size());

		// Rect Debug Mesh
		std::shared_ptr<Mesh> rectDebug = std::make_shared<Mesh>();
		Resources::Insert(L"DebugRect", rectDebug);
		rectDebug->CreateVertexBuffer(vertices.data(), vertices.size());
		rectDebug->CreateIndexBuffer(indices.data(), indices.size());

		vertices.clear();
		indices.clear();

		Vertex center = {};
		center.pos = Vector3(0.0f, 0.0f, 0.0f);
		center.color = Vector4(0.0f, 1.0f, 0.0f, 1.0f);
		vertices.push_back(center);

		int iSlice = 40;
		float fRadius = 0.5f;
		float fTheta = XM_2PI / (float)iSlice;

		for (int i = 0; i < iSlice; ++i)
		{
			center.pos = Vector3(fRadius * cosf(fTheta * (float)i)
				, fRadius * sinf(fTheta * (float)i)
				, 0.0f);
			center.color = Vector4(0.0f, 1.0f, 0.0f, 1.f);
			vertices.push_back(center);
		}

		for (int i = 0; i < vertices.size() - 2; ++i)
		{
			indices.push_back(i + 1);
		}
		indices.push_back(1);

		std::shared_ptr<Mesh> circleDebug = std::make_shared<Mesh>();
		Resources::Insert(L"DebugCircle", circleDebug);
		circleDebug->CreateVertexBuffer(vertices.data(), vertices.size());
		circleDebug->CreateIndexBuffer(indices.data(), indices.size());

	}

	void LoadBuffer()
	{	
		constantBuffer[(UINT)eCBType::Transform] = new ConstantBuffer(eCBType::Transform);
		constantBuffer[(UINT)eCBType::Transform]->Create(sizeof(TransformCB));

		constantBuffer[(UINT)eCBType::Time] = new ConstantBuffer(eCBType::Time);
		constantBuffer[(UINT)eCBType::Time]->Create(sizeof(TimeCB));

		constantBuffer[(UINT)eCBType::Grid] = new ConstantBuffer(eCBType::Grid);
		constantBuffer[(UINT)eCBType::Grid]->Create(sizeof(GridCB));

		constantBuffer[(UINT)eCBType::Debug] = new ConstantBuffer(eCBType::Debug);
		constantBuffer[(UINT)eCBType::Debug]->Create(sizeof(DebugCB));
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

		std::shared_ptr<Shader> debugShader = std::make_shared<Shader>();
		debugShader->Create(eShaderStage::VS, L"DebugVS.hlsl", "main");
		debugShader->Create(eShaderStage::PS, L"DebugPS.hlsl", "main");
		debugShader->SetTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D_PRIMITIVE_TOPOLOGY_LINESTRIP);
		debugShader->SetRSState(eRSType::SolidNone);
		Mn::Resources::Insert(L"DebugShader", debugShader);


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


		std::shared_ptr<Texture> TitleTex;
		TitleTex = Resources::Load<Texture>(L"Title_Scene", L"..\\Resources\\Texture\\BackGround\\Title_1.jpg");



		std::shared_ptr<Texture> SkyBackground;
		SkyBackground= Resources::Load<Texture>(L"BackGround_forest_sky", L"..\\Resources\\Texture\\BackGround\\background_stage_1_sky.png");
		
		
		std::shared_ptr<Texture> backgroundTex[4];
		backgroundTex[0] = Resources::Load<Texture>(L"BackGround_forest_ground", L"..\\Resources\\Texture\\BackGround\\background_stage_1_ground.png");
		backgroundTex[1] = Resources::Load<Texture>(L"BackGround_forest_tree", L"..\\Resources\\Texture\\BackGround\\background_stage_1_tree_1.png");
		backgroundTex[2] = Resources::Load<Texture>(L"BackGround_forest_light", L"..\\Resources\\Texture\\BackGround\\background_light.png");
		backgroundTex[3] = Resources::Load<Texture>(L"BackGround_forest_boss", L"..\\Resources\\Texture\\BackGround\\forestBoss.png");


		std::shared_ptr<Texture> stage2BackGroundTex[5];
		stage2BackGroundTex[0] = Resources::Load<Texture>(L"BackGround_Cave_backGround_1", L"..\\Resources\\Texture\\BackGround\\cave\\background1.png");
		stage2BackGroundTex[1] = Resources::Load<Texture>(L"BackGround_Cave_backGround_2", L"..\\Resources\\Texture\\BackGround\\cave\\background2.png");
		stage2BackGroundTex[2] = Resources::Load<Texture>(L"BackGround_Cave_rock_type_1", L"..\\Resources\\Texture\\BackGround\\cave\\background3.png");
		stage2BackGroundTex[3] = Resources::Load<Texture>(L"BackGround_Cave_rock_type_2", L"..\\Resources\\Texture\\BackGround\\cave\\background4a.png");
		stage2BackGroundTex[4] = Resources::Load<Texture>(L"BackGround_Cave_rock_type_3", L"..\\Resources\\Texture\\BackGround\\cave\\background4b.png");



		//----------------------------------------------------------------
		//							Material
		//----------------------------------------------------------------
		
		//forest
		std::shared_ptr<Material> TitleMaterial = std::make_shared<Material>();
		TitleMaterial->SetTexture(TitleTex);
		TitleMaterial->Shader(backgroundShader);
		TitleMaterial->RenderingMode(eRenderingMode::Opaque);
		Mn::Resources::Insert(L"TitleMaterial", TitleMaterial);

		std::shared_ptr<Material> backgroundMaterial = std::make_shared<Material>();
		backgroundMaterial->SetTexture(SkyBackground);
		backgroundMaterial->Shader(backgroundShader);
		backgroundMaterial->RenderingMode(eRenderingMode::Opaque);
		Mn::Resources::Insert(L"BackGroundMaterial_Sky", backgroundMaterial);

		std::shared_ptr<Material> backgroundMaterialGround = std::make_shared<Material>();
		backgroundMaterialGround->SetTexture(backgroundTex[0]);
		backgroundMaterialGround->Shader(backgroundShader);
		backgroundMaterialGround->RenderingMode(eRenderingMode::Transparent);
		Mn::Resources::Insert(L"BackGround_forest_Ground", backgroundMaterialGround);

		std::shared_ptr<Material> backgroundMaterialTree = std::make_shared<Material>();
		backgroundMaterialTree->SetTexture(backgroundTex[1]);
		backgroundMaterialTree->Shader(backgroundShader);
		backgroundMaterialTree->RenderingMode(eRenderingMode::Transparent);
		Mn::Resources::Insert(L"BackGroundMaterial_Tree", backgroundMaterialTree);

		std::shared_ptr<Material> backgroundMaterialLight = std::make_shared<Material>();
		backgroundMaterialLight->SetTexture(backgroundTex[2]);
		backgroundMaterialLight->Shader(backgroundShader);
		backgroundMaterialLight->RenderingMode(eRenderingMode::Transparent);
		Mn::Resources::Insert(L"BackGroundMaterial_Light", backgroundMaterialLight);

		std::shared_ptr<Material> backgroundMaterialBoss = std::make_shared<Material>();
		backgroundMaterialBoss->SetTexture(backgroundTex[3]);
		backgroundMaterialBoss->Shader(backgroundShader);
		backgroundMaterialBoss->RenderingMode(eRenderingMode::Opaque);
		Mn::Resources::Insert(L"BackGround_forest_Boss", backgroundMaterialBoss);


		//cave
		std::shared_ptr<Material> backgroundMaterialCaveWall1 = std::make_shared<Material>();
		backgroundMaterialCaveWall1->SetTexture(stage2BackGroundTex[0]);
		backgroundMaterialCaveWall1->Shader(backgroundShader);
		backgroundMaterialCaveWall1->RenderingMode(eRenderingMode::Opaque);
		Mn::Resources::Insert(L"BackGround_Cave_BackGround_1", backgroundMaterialCaveWall1);

		std::shared_ptr<Material> backgroundMaterialCaveWall2 = std::make_shared<Material>();
		backgroundMaterialCaveWall2->SetTexture(stage2BackGroundTex[1]);
		backgroundMaterialCaveWall2->Shader(backgroundShader);
		backgroundMaterialCaveWall2->RenderingMode(eRenderingMode::Transparent);
		Mn::Resources::Insert(L"BackGround_Cave_BackGround_2", backgroundMaterialCaveWall2);

		std::shared_ptr<Material> backgroundMaterialCaveRock1 = std::make_shared<Material>();
		backgroundMaterialCaveRock1->SetTexture(stage2BackGroundTex[2]);
		backgroundMaterialCaveRock1->Shader(backgroundShader);
		backgroundMaterialCaveRock1->RenderingMode(eRenderingMode::Transparent);
		Mn::Resources::Insert(L"BackGround_Cave_Rock_type_1", backgroundMaterialCaveRock1);

		std::shared_ptr<Material> backgroundMaterialCaveRock2 = std::make_shared<Material>();
		backgroundMaterialCaveRock2->SetTexture(stage2BackGroundTex[3]);
		backgroundMaterialCaveRock2->Shader(backgroundShader);
		backgroundMaterialCaveRock2->RenderingMode(eRenderingMode::Transparent);
		Mn::Resources::Insert(L"BackGround_Cave_Rock_type_2", backgroundMaterialCaveRock2);

		std::shared_ptr<Material> backgroundMaterialCaveRock3 = std::make_shared<Material>();
		backgroundMaterialCaveRock3->SetTexture(stage2BackGroundTex[4]);
		backgroundMaterialCaveRock3->Shader(backgroundShader);
		backgroundMaterialCaveRock3->RenderingMode(eRenderingMode::Transparent);
		Mn::Resources::Insert(L"BackGround_Cave_Rock_type_3", backgroundMaterialCaveRock3);


		//Water
		std::shared_ptr<Texture> WaterTex;
		WaterTex = Resources::Load<Texture>(L"Water_Bump", L"..\\Resources\\Texture\\Water\\Water_Bump.png");
		std::shared_ptr<Material> WaterMat = std::make_shared<Material>();
		WaterMat->SetTexture(WaterTex);
		//WaterMat->TextureBind(backgroundTex[0], 1);
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

		std::shared_ptr<Shader> gridShader
			= Resources::Find<Shader>(L"GridShader");

		std::shared_ptr<Shader> debugShader
			= Resources::Find<Shader>(L"DebugShader");
		
		//----------------------------------------------------------------
		//							Texture
		//----------------------------------------------------------------

		//HP
		std::shared_ptr<Texture> Hpbar = std::make_shared<Texture>();
		std::shared_ptr<Texture> HpbarBack = std::make_shared<Texture>();
		std::shared_ptr<Texture> HpbarFrame = std::make_shared<Texture>();
		Hpbar = Resources::Load<Texture>(L"HP_BAR_progressBar", L"..\\Resources\\Texture\\GUI\\HP_BAR\\BarV7_ProgressBar.png");
		HpbarBack = Resources::Load<Texture>(L"HP_BAR_back", L"..\\Resources\\Texture\\GUI\\HP_BAR\\BarV7_Bar.png");
		HpbarFrame = Resources::Load<Texture>(L"HP_BAR_fram", L"..\\Resources\\Texture\\GUI\\HP_BAR\\BarV7_ProgressBarBorder.png");

		//----------------------------------------------------------------
		//							Material
		//----------------------------------------------------------------

		//Hp
		std::shared_ptr<Material> progressHpMat = std::make_shared<Material>();
		progressHpMat->SetTexture(Hpbar);
		progressHpMat->Shader(HPShader);
		progressHpMat->RenderingMode(eRenderingMode::Transparent);
		Resources::Insert<Material>(L"HP_BAR_ProgressBar", progressHpMat);

		std::shared_ptr<Material> HpMat = std::make_shared<Material>();
		HpMat->SetTexture(HpbarBack);
		HpMat->Shader(HPShader);
		HpMat->RenderingMode(eRenderingMode::Transparent);
		Resources::Insert<Material>(L"HP_BAR_Back", HpMat);

		std::shared_ptr<Material> HpBarFrameMat = std::make_shared<Material>();
		HpBarFrameMat->SetTexture(HpbarFrame);
		HpBarFrameMat->Shader(HPShader);
		HpBarFrameMat->RenderingMode(eRenderingMode::Transparent);
		Resources::Insert<Material>(L"HP_BAR_FRAME", HpBarFrameMat);

		std::shared_ptr<Material> material = std::make_shared<Material>();
		material->Shader(gridShader);
		Resources::Insert(L"GridMaterial", material);

		material = std::make_shared<Material>();
		material->Shader(debugShader);
		Resources::Insert(L"DebugMaterial", material);

	}


	void Initialize()
	{
		LoadMesh();
		LoadBuffer();
		LoadShader();
		SetupState();
		LoadMaterial();
	}

	void PushDebugMeshAttribute(DebugMesh mesh)
	{
		debugMeshs.push_back(mesh);
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
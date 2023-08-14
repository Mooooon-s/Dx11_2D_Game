#include "MnRenderer.h"
#include "MnTexture.h"
#include "MnResources.h"
#include "MnMaterial.h"
#include "MnTime.h"
#include "MnStructedBuffer.h"

namespace renderer
{
	using namespace Mn;
	using namespace Mn::graphics;

	Mn::graphics::ConstantBuffer* constantBuffer[(UINT)eCBType::End] = {};
	Microsoft::WRL::ComPtr<ID3D11SamplerState> samplerState[(UINT)eSamplerType::End] = {};
	
	Microsoft::WRL::ComPtr<ID3D11RasterizerState> rasterizerStates[(UINT)eRSType::End] = {};
	Microsoft::WRL::ComPtr<ID3D11DepthStencilState> depthStencilStates[(UINT)eDSType::End] = {};
	Microsoft::WRL::ComPtr<ID3D11BlendState> blendStates[(UINT)eBSType::End] = {};

	//Light
	std::vector<Light*> lights = {};
	StructedBuffer* lightsBuffer = nullptr;

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

		std::shared_ptr <Shader> HPshader = Mn::Resources::Find<Shader>(L"TopbarShader");
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

		std::shared_ptr <Shader> AnimationShader = Mn::Resources::Find<Shader>(L"SpriteAnimationShader");
		Mn::graphics::GetDevice()->CreateInputLayout(arrLayout, 3
			, AnimationShader->GetVSCode()
			, AnimationShader->GetInputLayoutAddressOf());


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

		constantBuffer[(UINT)eCBType::Animator] = new ConstantBuffer(eCBType::Animator);
		constantBuffer[(UINT)eCBType::Animator]->Create(sizeof(AnimatorCB));

		constantBuffer[(UINT)eCBType::Flip] = new ConstantBuffer(eCBType::Flip);
		constantBuffer[(UINT)eCBType::Flip]->Create(sizeof(FlipCB));

		//structed buffer
		lightsBuffer = new StructedBuffer();
		lightsBuffer->Create(sizeof(LightAttribute), 2, eSRVType::None);
	
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
		std::shared_ptr<Shader> Topbarshader = std::make_shared<Shader>();
		Topbarshader->Create(eShaderStage::VS, L"TopbarVS.hlsl", "main");
		Topbarshader->Create(eShaderStage::PS, L"TopbarPS.hlsl", "main");
		Mn::Resources::Insert(L"TopbarShader", Topbarshader);

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

		std::shared_ptr<Shader> animationShader = std::make_shared<Shader>();
		animationShader->Create(eShaderStage::VS, L"SpriteAnimationVS.hlsl", "main");
		animationShader->Create(eShaderStage::PS, L"SpriteAnimationPS.hlsl", "main");
		Mn::Resources::Insert(L"SpriteAnimationShader", animationShader);

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

		std::shared_ptr<Shader> animationShader
			= Resources::Find<Shader>(L"SpriteShader");
		// 
		//----------------------------------------------------------------
		//							Texture
		//----------------------------------------------------------------
		std::shared_ptr<Mn::graphics::Texture> texture = Resources::Load<Mn::graphics::Texture>(L"player", L"..\\Resources\\Texture\\idle.png");

		//----------------------------------------------------------------
		//							Material
		//----------------------------------------------------------------
		std::shared_ptr <Material> spriteMaterial = std::make_shared<Material>();
		spriteMaterial->SetTexture(texture);
		spriteMaterial->Shader(spriteShader);
		spriteMaterial->RenderingMode(eRenderingMode::Transparent);
		Mn::Resources::Insert(L"SpriteMaterial", spriteMaterial);

		spriteShader = Resources::Find<Shader>(L"SpriteAnimationShader");
		std::shared_ptr <Material> Animaterial = std::make_shared<Material>();
		Animaterial->Shader(spriteShader);
		Animaterial->RenderingMode(eRenderingMode::Transparent);
		Resources::Insert(L"SpriteAnimaionMaterial", Animaterial);

		//---------------------------------------------------------------------------------------------------------------------------------------
		//
		//																Item
		//
		//---------------------------------------------------------------------------------------------------------------------------------------
		// ---------------------------------------------------------------
		//							Shader
		// ---------------------------------------------------------------
		// 
		spriteShader = Resources::Find<Shader>(L"SpriteAnimationShader");
		// 
		//----------------------------------------------------------------
		//							Texture
		//----------------------------------------------------------------
		//std::shared_ptr<Mn::graphics::Texture> FoodTexture = Resources::Load<Mn::graphics::Texture>(L"FoodTex", L"..\\Resources\\Texture\\Food\\food.jpg");
		//std::shared_ptr<Mn::graphics::Texture> FoodTextureAlpha = Resources::Load<Mn::graphics::Texture>(L"FoodTex_alpha", L"..\\Resources\\Texture\\Food\\_food.jpg");

		//----------------------------------------------------------------
		//							Material
		//----------------------------------------------------------------
		
		std::shared_ptr <Material> FoodAnimaterial = std::make_shared<Material>();
		FoodAnimaterial->Shader(spriteShader);
		FoodAnimaterial->RenderingMode(eRenderingMode::Transparent);
		Resources::Insert(L"FoodSpriteAnimaionMaterial", FoodAnimaterial);

		std::shared_ptr <Material> coinAnimaterial = std::make_shared<Material>();
		coinAnimaterial->Shader(spriteShader);
		coinAnimaterial->RenderingMode(eRenderingMode::Transparent);
		Resources::Insert(L"CoinSpriteAnimaionMaterial", coinAnimaterial);



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
		std::shared_ptr<Mn::graphics::Texture> Montexture = Resources::Load<Mn::graphics::Texture>(L"Monster_Pumpkin", L"..\\Resources\\Texture\\Monster\\Undead_pumpking_Sprites.png");

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
		//----------------------------------------------------------------
		//							Texture
		//----------------------------------------------------------------

		std::shared_ptr<Mn::graphics::Texture> TitleTex;
		TitleTex = Resources::Load<Mn::graphics::Texture>(L"Title_Scene", L"..\\Resources\\Texture\\BackGround\\titlescreen.jpg");

		std::shared_ptr<Mn::graphics::Texture> MenuTex;
		MenuTex = Resources::Load<Mn::graphics::Texture>(L"Menu_Scene", L"..\\Resources\\Texture\\BackGround\\selectorback.jpg");

		std::shared_ptr<Mn::graphics::Texture> StageBackGround[6];
		StageBackGround[0] = Resources::Load<Mn::graphics::Texture>(L"Stage_1_BackGround", L"..\\Resources\\Texture\\BackGround\\aquarium1.jpg");
		StageBackGround[1] = Resources::Load<Mn::graphics::Texture>(L"Stage_2_BackGround", L"..\\Resources\\Texture\\BackGround\\aquarium2.jpg");
		StageBackGround[2] = Resources::Load<Mn::graphics::Texture>(L"Stage_3_BackGround", L"..\\Resources\\Texture\\BackGround\\aquarium3.jpg");
		StageBackGround[3] = Resources::Load<Mn::graphics::Texture>(L"Stage_4_BackGround", L"..\\Resources\\Texture\\BackGround\\aquarium4.jpg");
		StageBackGround[4] = Resources::Load<Mn::graphics::Texture>(L"Stage_5_BackGround", L"..\\Resources\\Texture\\BackGround\\aquarium5.jpg");
		StageBackGround[5] = Resources::Load<Mn::graphics::Texture>(L"Stage_6_BackGround", L"..\\Resources\\Texture\\BackGround\\aquarium6.jpg");
		//----------------------------------------------------------------
		//							Material
		//----------------------------------------------------------------

		//Title
		std::shared_ptr<Material> TitleMaterial = std::make_shared<Material>();
		TitleMaterial->SetTexture(TitleTex);
		TitleMaterial->Shader(backgroundShader);
		TitleMaterial->RenderingMode(eRenderingMode::Opaque);
		Mn::Resources::Insert(L"TitleMaterial", TitleMaterial);

		std::shared_ptr<Material> MenuMaterial = std::make_shared<Material>();
		MenuMaterial->SetTexture(MenuTex);
		MenuMaterial->Shader(backgroundShader);
		MenuMaterial->RenderingMode(eRenderingMode::Opaque);
		Mn::Resources::Insert(L"Menu_Material", MenuMaterial);

		std::shared_ptr<Material> StageMaterial1 = std::make_shared<Material>();
		StageMaterial1->SetTexture(StageBackGround[0]);
		StageMaterial1->Shader(backgroundShader);
		StageMaterial1->RenderingMode(eRenderingMode::Opaque);
		Mn::Resources::Insert(L"Stage_1_background", StageMaterial1);

		std::shared_ptr<Material> StageMaterial2 = std::make_shared<Material>();
		StageMaterial2->SetTexture(StageBackGround[1]);
		StageMaterial2->Shader(backgroundShader);
		StageMaterial2->RenderingMode(eRenderingMode::Opaque);
		Mn::Resources::Insert(L"Stage_2_background", StageMaterial2);

		std::shared_ptr<Material> StageMaterial3 = std::make_shared<Material>();
		StageMaterial3->SetTexture(StageBackGround[2]);
		StageMaterial3->Shader(backgroundShader);
		StageMaterial3->RenderingMode(eRenderingMode::Opaque);
		Mn::Resources::Insert(L"Stage_3_background", StageMaterial3);

		std::shared_ptr<Material> StageMaterial4 = std::make_shared<Material>();
		StageMaterial4->SetTexture(StageBackGround[3]);
		StageMaterial4->Shader(backgroundShader);
		StageMaterial4->RenderingMode(eRenderingMode::Opaque);
		Mn::Resources::Insert(L"Stage_4_background", StageMaterial4);

		std::shared_ptr<Material> StageMaterial5 = std::make_shared<Material>();
		StageMaterial5->SetTexture(StageBackGround[4]);
		StageMaterial5->Shader(backgroundShader);
		StageMaterial5->RenderingMode(eRenderingMode::Opaque);
		Mn::Resources::Insert(L"Stage_5_background", StageMaterial5);

		std::shared_ptr<Material> StageMaterial6 = std::make_shared<Material>();
		StageMaterial6->SetTexture(StageBackGround[5]);
		StageMaterial6->Shader(backgroundShader);
		StageMaterial6->RenderingMode(eRenderingMode::Opaque);
		Mn::Resources::Insert(L"Stage_6_background", StageMaterial6);

		//---------------------------------------------------------------------------------------------------------------------------------------
		//
		//																GUI
		//
		//---------------------------------------------------------------------------------------------------------------------------------------
		// ---------------------------------------------------------------
		//							Shader
		// ---------------------------------------------------------------
		std::shared_ptr<Shader>  TopBarShader
			= Resources::Find<Shader>(L"TopbarShader");

		std::shared_ptr<Shader> gridShader
			= Resources::Find<Shader>(L"GridShader");

		std::shared_ptr<Shader> debugShader
			= Resources::Find<Shader>(L"DebugShader");
		
		//----------------------------------------------------------------
		//							Texture
		//----------------------------------------------------------------

		//HP
		std::shared_ptr<Mn::graphics::Texture> TopBarTex = std::make_shared<Mn::graphics::Texture>();
		TopBarTex = Resources::Load<Mn::graphics::Texture>(L"Top_Bar_Texture", L"..\\Resources\\Texture\\UI\\bar\\menubar.jpg");

		//----------------------------------------------------------------
		//							Material
		//----------------------------------------------------------------


		std::shared_ptr<Material> BarMaterial = std::make_shared<Material>();
		BarMaterial->SetTexture(TopBarTex);
		BarMaterial->Shader(TopBarShader);
		Resources::Insert(L"TopBar_Material", BarMaterial);

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

	void BindLights()
	{
		std::vector<LightAttribute> lightsAttributes = {};
		for (Light* light : lights)
		{
			LightAttribute attribute = light->GetAttribute();
			lightsAttributes.push_back(attribute);
		}

		lightsBuffer->SetData(lightsAttributes.data(), lightsAttributes.size());
		lightsBuffer->Bind(eShaderStage::VS, 14);
		lightsBuffer->Bind(eShaderStage::PS, 14);
	}

	void PushDebugMeshAttribute(DebugMesh mesh)
	{
		debugMeshs.push_back(mesh);
	}


	void Render()
	{
		BindLights();

		for (Camera* cam : cameras)
		{
			if (cam == nullptr)
				continue;

			cam->Render();
		}

		cameras.clear();
		lights.clear();
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

		delete lightsBuffer;
		lightsBuffer = nullptr;
	}
}
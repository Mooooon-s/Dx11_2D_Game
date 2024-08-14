#include "StartButtonBarRender.h"
#include "MnResources.h"
#include "MnAnimator.h"
#include "MnMeshRenderer.h"
#include "MnSceneManager.h"

Mn::StartButtonBarRender::StartButtonBarRender()
{
}

Mn::StartButtonBarRender::~StartButtonBarRender()
{
}

void Mn::StartButtonBarRender::Initialize()
{

	Transform* tr = GetComponent<Transform>();
	tr->Scale(1.85f, 0.25f, 1.f);
	tr->Position(-0.1035f, -1.425, 1.1f);

	Collider2D* coll = AddComponent<Collider2D>();

	MeshRenderer* mr = AddComponent<MeshRenderer>();
	mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
	mr->SetMaterial(Resources::Find<Material>(L"SpriteAnimaionMaterial"));
	Animator* at = AddComponent<Animator>();



	std::shared_ptr<Mn::graphics::Texture> baratlas
		= Resources::Load<Mn::graphics::Texture>(L"StartButton_bar_On_Sprite", L"..\\Resources\\Texture\\UI\\bar\\loaderbarover.jpg");
	std::shared_ptr<Mn::graphics::Texture> baratlasAlpha
		= Resources::Load<Mn::graphics::Texture>(L"StartButton_bar_On_Sprite_Alpha", L"..\\Resources\\Texture\\UI\\bar\\loaderbarover_.jpg");
	at->Create(L"StartButton_bar_On", baratlas, baratlasAlpha, Vector2::Zero, Vector2(250.f, 31.5f), 1, Vector2::Zero, 0.1f);

	std::shared_ptr<Mn::graphics::Texture> atlas
		= Resources::Load<Mn::graphics::Texture>(L"StartButton_bar_Sprite", L"..\\Resources\\Texture\\UI\\bar\\loaderbar.jpg");
	std::shared_ptr<Mn::graphics::Texture> atlasAlpha
		= Resources::Load<Mn::graphics::Texture>(L"StartButton_bar_Sprite_Alpha", L"..\\Resources\\Texture\\UI\\bar\\loaderbar_.jpg");
	at->Create(L"StartButton_bar", atlas, atlasAlpha, Vector2::Zero, Vector2(250.f, 31.5f), 1, Vector2::Zero, 0.1f);

	at->PlayAnimation(L"StartButton_bar", true);
}

void Mn::StartButtonBarRender::Update()
{
	GameObject::Update();
}

void Mn::StartButtonBarRender::LateUpdate()
{
	GameObject::LateUpdate();
}

void Mn::StartButtonBarRender::Render()
{
	GameObject::Render();
}

void Mn::StartButtonBarRender::FontRender()
{
}

void Mn::StartButtonBarRender::OnClick()
{
}

void Mn::StartButtonBarRender::OnClick(Vector3 pos)
{
	SceneManager::LoadScene(L"MenuScene");
}

void Mn::StartButtonBarRender::MouseOn()
{
	GetComponent<Animator>()->PlayAnimation(L"StartButton_bar_On",true);
}

void Mn::StartButtonBarRender::MouseOff()
{
	GetComponent<Animator>()->PlayAnimation(L"StartButton_bar", true);
}

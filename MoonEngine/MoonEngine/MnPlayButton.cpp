#include "MnPlayButton.h"
#include "MnResources.h"
#include "MnAnimator.h"
#include "MnSceneManager.h"
#include "MnFontWrapper.h"


namespace Mn
{
	PlayButton::PlayButton()
		: _Animator(nullptr)
		, _szFloat(L"Start Game")
	{
	}
	PlayButton::~PlayButton()
	{
	}
	void PlayButton::Initialize()
	{
		Transform* tr = GetComponent<Transform>();
		tr->Scale(Vector3(1.65f, 0.5f, 0.0f));

		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"SpriteAnimaionMaterial"));
		mr->FlipX(0);

		Collider2D* coll = AddComponent<Collider2D>();
		coll->SetSize(Vector2(1,1));

		_Animator = AddComponent<Animator>();

		std::shared_ptr<Mn::graphics::Texture> atlas
			= Resources::Load<Mn::graphics::Texture>(L"Start_Button_On", L"..\\Resources\\Texture\\UI\\button\\battletankbutton.jpg");
		std::shared_ptr<Mn::graphics::Texture> atlasAlpha
			= Resources::Load<Mn::graphics::Texture>(L"Start_Button_On_Alpha", L"..\\Resources\\Texture\\UI\\button\\_battletankbutton.jpg");
		_Animator->Create(L"StartButton_MouseOn", atlas, atlasAlpha, Vector2::Zero, Vector2(217, 66), 1, Vector2::Zero, 0.01f);
		
		atlasAlpha = Resources::Load<Mn::graphics::Texture>(L"Start_Button_Idle_Alpha", L"..\\Resources\\Texture\\UI\\button\\_battletankbuttonIdle.jpg");
		_Animator->Create(L"StartButton_Idle", atlas, atlasAlpha, Vector2::Zero, Vector2(217, 66), 1, Vector2::Zero, 0.01f);

		atlas = Resources::Load<Mn::graphics::Texture>(L"Start_Button_Click", L"..\\Resources\\Texture\\UI\\button\\battletankbuttond.jpg");
		atlasAlpha = Resources::Load<Mn::graphics::Texture>(L"Start_Button_Click_Alpha", L"..\\Resources\\Texture\\UI\\button\\_battletankbuttond.jpg");
		_Animator->Create(L"StartButton_Down", atlas, atlasAlpha, Vector2::Zero, Vector2(217, 66), 1, Vector2::Zero, 0.01f);

		_Animator->PlayAnimation(L"StartButton_Idle", true);

	}
	void PlayButton::Update()
	{
		GameObject::Update();
	}
	void PlayButton::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void PlayButton::Render()
	{
		GameObject::Render();
	}
	void PlayButton::FontRender()
	{
		FontWrapper::DrawFont(_szFloat, 600, 100, 40, FONT_RGBA(255, 0, 255, 255));
		GameObject::FontRender();
	}
	void PlayButton::OnClick()
	{
	}
	void PlayButton::OnClick(Vector3 pos)
	{
		_Animator->PlayAnimation(L"StartButton_Down", true);
		SceneManager::LoadScene(L"PlayScene");
	}
	void PlayButton::MouseOn()
	{
		if (_Animator->AnimationComplete())
			_Animator->PlayAnimation(L"StartButton_MouseOn", true);
	}
	void PlayButton::MouseOff()
	{
		if (_Animator->AnimationComplete())
			_Animator->PlayAnimation(L"StartButton_Idle", true);
	}
}
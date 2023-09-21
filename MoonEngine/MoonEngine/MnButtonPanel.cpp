#include "MnButtonPanel.h"
#include "MnMeshRenderer.h"
#include "MnResources.h"
#include "MnAnimator.h"
#include "MnCollider2D.h"
#include "MnEventManager.h"

#include "MnEventManager.h"
#include "MnSceneManager.h"

namespace Mn
{
	ButtonPanel::ButtonPanel()
		: _Animator(nullptr)
		, _Icon(eIcon::Guppy)
		, _EventManager(nullptr)
	{
	}
	ButtonPanel::~ButtonPanel()
	{
	}
	void ButtonPanel::Initialize()
	{
		Scene* scene = SceneManager::ActiveScene();
		std::vector<GameObject*> gameObj = scene->GetLayer(eLayerType::UI).GetGameObjects();
		for (auto obj : gameObj)
		{
			if (dynamic_cast<EventManager*>(obj))
				_EventManager = dynamic_cast<EventManager*>(obj);
		}

		Transform* tr = GetComponent<Transform>();
		tr->Scale(Vector3(0.4f, 0.4f, 0.0f));

		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"SpriteAnimaionMaterial"));
		mr->FlipX(1);

		Collider2D* coll = AddComponent<Collider2D>();
		coll->SetSize(Vector2(0.5,0.5));

		_Animator = AddComponent<Animator>();

		std::shared_ptr<Mn::graphics::Texture> atlas
			= Resources::Load<Mn::graphics::Texture>(L"Hatch_Panel_Idle", L"..\\Resources\\Texture\\UI\\bar\\mbuttonu.jpg");
		std::shared_ptr<Mn::graphics::Texture> atlasAlpha
			= Resources::Load<Mn::graphics::Texture>(L"Hatch_Panel_Idle_Alpha", L"..\\Resources\\Texture\\UI\\bar\\_mbuttonu.jpg");

		_Animator->Create(L"PanelIdle", atlas, atlasAlpha, Vector2::Zero, Vector2(57, 60), 1, Vector2::Zero, 0.1f);


		atlas = Resources::Load<Mn::graphics::Texture>(L"Hatch_Panel_On", L"..\\Resources\\Texture\\UI\\bar\\mbuttono.jpg");
		atlasAlpha = Resources::Load<Mn::graphics::Texture>(L"Hatch_Panel_On_Alpha", L"..\\Resources\\Texture\\UI\\bar\\_mbuttono.jpg");
		_Animator->Create(L"PanelOn", atlas, atlasAlpha, Vector2::Zero, Vector2(57, 60), 1, Vector2::Zero, 0.1f);

		atlas = Resources::Load<Mn::graphics::Texture>(L"Hatch_Panel_OnClick", L"..\\Resources\\Texture\\UI\\bar\\mbuttond.jpg");
		atlasAlpha = Resources::Load<Mn::graphics::Texture>(L"Hatch_Panel_OnClick_Alpha", L"..\\Resources\\Texture\\UI\\bar\\_mbuttond.jpg");
		_Animator->Create(L"PanelOnClick", atlas, atlasAlpha, Vector2::Zero, Vector2(57, 60), 1, Vector2::Zero, 0.1f);

		_Animator->PlayAnimation(L"PanelIdle", false);
	}
	void ButtonPanel::Update()
	{
		GameObject::Update();
	}
	void ButtonPanel::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void ButtonPanel::Render()
	{
		GameObject::Render();
	}
	void ButtonPanel::OnClick(Vector3 pos)
	{
		_Animator->PlayAnimation(L"PanelOnClick", true);
		_EventManager->ButtonEvent(_Icon);


	}
	void ButtonPanel::MouseOn()
	{
		if(_Animator->AnimationComplete())
			_Animator->PlayAnimation(L"PanelOn", true);
	}
	void ButtonPanel::MouseOff()
	{
		if (_Animator->AnimationComplete())
			_Animator->PlayAnimation(L"PanelIdle", true);
	}
}
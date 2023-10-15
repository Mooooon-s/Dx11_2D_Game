#include "MnPregoRnder.h"
#include "MnGameObject.h"
#include "MnResources.h"
#include "MnAnimator.h"
#include "MnMeshRenderer.h"

namespace Mn
{
	PregoRnder::PregoRnder()
	{
	}
	PregoRnder::~PregoRnder()
	{
	}
	void PregoRnder::Initialize()
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();
		tr->Scale(Vector3(0.5f, 0.5f, 0.0f));

		MeshRenderer* mr = GetOwner()->AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"SpriteAnimaionMaterial"));

		Animator* at = GetOwner()->AddComponent<Animator>();
		std::shared_ptr<Mn::graphics::Texture> atlas
			= Resources::Load<Mn::graphics::Texture>(L"Prego_Atlas", L"..\\Resources\\Texture\\Pet\\prego\\prego.jpg");
		std::shared_ptr<Mn::graphics::Texture> atlasAlpha
			= Resources::Load<Mn::graphics::Texture>(L"Prego_Atlas_alpha", L"..\\Resources\\Texture\\Pet\\prego\\_prego.jpg");

		at->Create(L"Prego_Swim", atlas, atlasAlpha, Vector2::Zero, Vector2(80.0f, 80.0f), 10, Vector2::Zero, 0.1f);
		at->Create(L"Prego_Preg_Swim", atlas, atlasAlpha, Vector2(0.0f,80.0f), Vector2(80.0f,80.0f), 10, Vector2::Zero, 0.1f);
		at->Create(L"Prego_Turn", atlas, atlasAlpha, Vector2(0.0f,160.0f), Vector2(80.0f,80.0f), 10, Vector2::Zero, 0.1f);
		at->CreateReverse(L"Prego_Turn_Reverse", atlas, atlasAlpha, Vector2(0.0f,160.0f), Vector2(80.0f,80.0f), 10, Vector2::Zero, 0.1f);
		at->Create(L"Prego_preg_Turn", atlas, atlasAlpha, Vector2(0.0f, 160.0f), Vector2(80.0f, 80.0f), 10, Vector2::Zero, 0.1f);
		at->CreateReverse(L"Prego_preg_Turn_Reverse", atlas, atlasAlpha, Vector2(0.0f, 160.0f), Vector2(80.0f, 80.0f), 10, Vector2::Zero, 0.1f);
		at->Create(L"Prego_preg_Guppy", atlas, atlasAlpha, Vector2(0.0f,240.0f), Vector2(80.0f,80.0f),5, Vector2::Zero, 0.1f);
		at->CreateReverse(L"Prego_Out_Guppy", atlas, atlasAlpha, Vector2(400.0f,240.0f), Vector2(80.0f,80.0f),5, Vector2::Zero, 0.1f);


		at->CompleteEvent(L"Prego_Turn") = std::bind(&PregoRnder::afterAction, this);
		at->CompleteEvent(L"Prego_Turn_Reverse") = std::bind(&PregoRnder::afterAction, this);
		
		at->CompleteEvent(L"Prego_preg_Turn") = std::bind(&PregoRnder::afterPregTurn, this);
		at->CompleteEvent(L"Prego_preg_Turn_Reverse") = std::bind(&PregoRnder::afterPregTurn, this);
		
		at->CompleteEvent(L"Prego_Out_Guppy") = std::bind(&PregoRnder::afterPreg, this);
		at->CompleteEvent(L"Prego_preg_Guppy") = std::bind(&PregoRnder::PregGuppy, this);

		at->PlayAnimation(L"Prego_Swim", true);
	}
	void PregoRnder::Update()
	{
	}
	void PregoRnder::LateUpdate()
	{
	}
	void PregoRnder::Render()
	{
	}
	void PregoRnder::afterAction()
	{
		Animator* at = GetOwner()->GetComponent<Animator>();
		at->PlayAnimation(L"Prego_Swim",true);
	}
	void PregoRnder::afterPreg()
	{
		Animator* at = GetOwner()->GetComponent<Animator>();
		at->PlayAnimation(L"Prego_Swim", true);
	}
	void PregoRnder::PregGuppy()
	{
		Animator* at = GetOwner()->GetComponent<Animator>();
		at->PlayAnimation(L"Prego_Preg_Swim", true);
	}
	void PregoRnder::afterPregTurn()
	{
		Animator* at = GetOwner()->GetComponent<Animator>();
		at->PlayAnimation(L"Prego_Preg_Swim", true);
	}
}
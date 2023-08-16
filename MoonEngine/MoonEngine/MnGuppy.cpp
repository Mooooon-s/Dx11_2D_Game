#include "MnGuppy.h"

#include "MnMeshRenderer.h"
#include "MnResources.h"
#include "MnTexture.h"
#include "MnAnimator.h"
#include "MnCollider2D.h"
#include "MnGuppyScript.h"

#include "MnGuppyRenderScript.h"
#include "MnGuppyAnimationCntrl.h"

#include "MnGuppyBehaviorTree.h"

namespace Mn
{
	Guppy::Guppy()
	{
	}
	Guppy::~Guppy()
	{
	}
	void Guppy::Initialize()
	{
		Transform* tr = GetComponent<Transform>();
		tr->Scale(Vector3(0.8, 0.8, 0.0f));
		SetName(L"Guppy");
		Collider2D* col = AddComponent<Collider2D>();
		col->SetSize(Vector2(0.25f, 0.25f));

		GuppyRender* GR = AddComponent<GuppyRender>();
		//GR->Initialize();

		GuppyBehaviorTree* GBT = AddComponent<GuppyBehaviorTree>();
		//GBT->Initialize();
		GameObject::Initialize();
	}
	void Guppy::Update()
	{
		GameObject::Update();
	}
	void Guppy::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void Guppy::Render()
	{
		GameObject::Render();
	}
}
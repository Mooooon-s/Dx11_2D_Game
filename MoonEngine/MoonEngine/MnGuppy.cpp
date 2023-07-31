#include "MnGuppy.h"

#include "MnMeshRenderer.h"
#include "MnResources.h"
#include "MnTexture.h"
#include "MnAnimator.h"
#include "MnCollider2D.h"
#include "MnGuppyScript.h"

#include "MnGuppyRenderScript.h"
#include "MnGuppyAnimationCntrl.h"


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
		SetName(L"Guppy");
		Collider2D* col = AddComponent<Collider2D>();
		col->SetSize(Vector2(1.0f, 1.0f));

		GuppyRender* GR = AddComponent<GuppyRender>();
		GR->Initialize();

		GuppyScript* GS = AddComponent<GuppyScript>();
		GS->Initialize();

		/*GuppyAnimationCntrl* GSC = AddComponent<GuppyAnimationCntrl>();
		GSC->Initialize();*/

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
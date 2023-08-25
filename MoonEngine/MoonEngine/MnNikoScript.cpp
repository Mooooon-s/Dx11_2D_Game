#include "MnNikoScript.h"
#include "MnTime.h"
#include "MnAnimator.h"
#include "MnGameObject.h"
#include "MnSceneManager.h"
#include "MnMoney.h"

namespace Mn
{
	NikoScript::NikoScript()
		:_Time(0.0f)
		, _Open(false)
	{
	}
	NikoScript::~NikoScript()
	{
	}
	void NikoScript::Initialize()
	{
	}
	void NikoScript::Update()
	{
		if(_Open==false)
			_Time += Time::DeltaTime();
		if (_Time >= 10)
		{
			_Open = true;
			Animator* at = GetOwner()->GetComponent<Animator>();
			at->PlayAnimation(L"Niko_Open",false);
			_Time = 0;
		}
	}
	void NikoScript::LateUpdate()
	{
	}
	void NikoScript::Render()
	{
	}
	void NikoScript::OnCollisionEnter(Collider2D* other)
	{
	}
	void NikoScript::OnCollisionStay(Collider2D* other)
	{
	}
	void NikoScript::OnCollisionExit(Collider2D* other)
	{
	}
	void NikoScript::OnClick()
	{
		if (_Open == true)
		{
			Scene* scene = SceneManager::ActiveScene();
			std::vector<GameObject*> gameObj = scene->GetLayer(eLayerType::UI).GetGameObjects();
			for (GameObject* obj : gameObj)
			{
				if (dynamic_cast<Money*>(obj))
					dynamic_cast<Money*>(obj)->EarnMoney(250);
			}
			Animator* at =GetOwner()->GetComponent<Animator>();
			at->PlayAnimation(L"Niko_Close", true);
			_Open = false;
		}
	}
}
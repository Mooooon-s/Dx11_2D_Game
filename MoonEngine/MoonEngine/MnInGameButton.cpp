#include "MnInGameButton.h"
#include "MnButtonFrame.h"
#include "MnButtonPanel.h"
#include "MnPriceTag.h"
#include "MnObject.h"
#include "MnCreateIcon.h"


#include "MnGuppyIcon.h"
#include "MnEggIcon.h"
#include "MnFoodIcon.h"
#include "MnFoodLevelIcon.h"
#include "MnCaniboarIcon.h"
#include "MnUltravoreIcon.h"

#include "MnSceneManager.h"
#include "MnEventManager.h"

namespace Mn
{
	InGameButton::InGameButton()
	: _IconObject(nullptr)
	, _PT(nullptr)
	{
	}
	InGameButton::~InGameButton()
	{
	}
	void InGameButton::Initialize()
	{
		Transform* tr = GetComponent<Transform>();
		Vector3 pos = tr->Position();
		ButtonFrame* BF = object::Instantiate<ButtonFrame>(pos, eLayerType::UI);
		BF->Initialize();

		pos.z += 0.01;
		Icon(pos);
		pos.z += 0.01;
		
		ButtonPanel* BP = object::Instantiate<ButtonPanel>(pos, eLayerType::UI);
		BP->SetIcon(_Icon);
		BP->Initialize();
		
		_PT = object::Instantiate<PriceTag>(pos, eLayerType::UI);
		_PT->SetPrice(BP->GetPrice());
		_PT->SetIcon(_Icon);
		_PT->SetPosition();
		_PT->Initialize();
	}
	void InGameButton::Update()
	{
		dynamic_cast<PriceTag*>(_PT)->TagOnOff(dynamic_cast<EventManager*>(SceneManager::ActiveScene()->GetLayer(eLayerType::Manager).GetGameObjects()[0])->GetEggCracking());
		GameObject::Update();
	}
	void InGameButton::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void InGameButton::Render()
	{
		GameObject::Render();
	}
	void InGameButton::OnClick()
	{
		if (_Icon == eIcon::Food)
			_IconObject->OnClick();
		if (_Icon == eIcon::FoodCount)
			_IconObject->OnClick();
		if (_Icon == eIcon::Egg)
			_IconObject->OnClick();
	}
	void InGameButton::MouseOn()
	{
	}
	void InGameButton::Icon(Vector3 pos)
	{
		switch (_Icon)
		{
		case Mn::enums::eIcon::Guppy:
			_IconObject = CreateIcon<GuppyIcon>(pos);
			_IconObject->Initialize();
			break;
		case Mn::enums::eIcon::Food:
			_IconObject = CreateIcon<FoodIcon>(pos);
			_IconObject->Initialize();
			break;
		case Mn::enums::eIcon::FoodCount:
			_IconObject = CreateIcon<FoodLevelIcon>(pos);
			_IconObject->Initialize();
			break;
		case Mn::enums::eIcon::Caniboar:
			_IconObject = CreateIcon<CaniboarIcon>(pos);
			_IconObject->Initialize();
			break;
		case Mn::enums::eIcon::Ultravore:
			_IconObject = CreateIcon<UltravoreIcon>(pos);
			_IconObject->Initialize();
			break;
		case Mn::enums::eIcon::Egg:
			_IconObject = CreateIcon<EggIcon>(pos);
			_IconObject->Initialize();
			break;
		case Mn::enums::eIcon::End:
			break;
		default:
			break;
		}
	}
}
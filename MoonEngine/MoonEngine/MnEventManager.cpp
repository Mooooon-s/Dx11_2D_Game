#include "MnEventManager.h"

#include <random>

#include "MnTime.h"
#include "MnWarp.h"
#include "MnObject.h"
#include "MnMouse.h"

#include "MnGuppy.h"
#include "MnCaniboar.h"
#include "MnUltravore.h"
#include "MnInGameButton.h"
#include "MnMoney.h"

namespace Mn
{
	EventManager::EventManager()
		: _Time(0.0f)
		, _EventStack(0)
		, _BossStack(0)
		, _BarSlotCount()
		, _FoodLevel(nullptr)
		, _FoodCount(nullptr)
		, _EggStack(1)
	{
	}
	EventManager::~EventManager()
	{
	}
	void EventManager::Initialize()
	{
		_BarSlotCount.resize(7,(float)0.00001f);
		_BarSlotCount[(UINT)eIcon::Caniboar] = (float)eIcon::Caniboar+0.0001;
		_BarSlotCount[(UINT)eIcon::Ultravore] = (float)eIcon::Ultravore+0.0001;

		InGameButton* IGBGuppy = object::Instantiate<InGameButton>(Vector3(-2.035f, 1.56f, -0.001f), eLayerType::UI);
		IGBGuppy->SetIcon(eIcon::Guppy);
		IGBGuppy->Initialize();

		_EggButton = object::Instantiate<InGameButton>(Vector3(1.085f, 1.56f, -0.001f), eLayerType::UI);
		_EggButton->SetIcon(eIcon::Egg);
		_EggButton->Initialize();

		//_FoodLevel = object::Instantiate<InGameButton>(Vector3(-1.525f, 1.56f, -0.001f), eLayerType::UI);
		//_FoodLevel->SetIcon(eIcon::Food);
		//_FoodLevel->Initialize();

		//_FoodCount = object::Instantiate<InGameButton>(Vector3(-1.1f, 1.56f, -0.001f), eLayerType::UI);
		//_FoodCount->SetIcon(eIcon::FoodCount);
		//_FoodCount->Initialize();

		//_CaniboarButton = object::Instantiate<InGameButton>(Vector3(-0.55, 1.56, -0.001f), eLayerType::UI);
		//_CaniboarButton->SetIcon(eIcon::Ultravore);
		//_CaniboarButton->Initialize();
	}
	void EventManager::Update()
	{
		OpenButton();
		_Time += Time::DeltaTime();
		Timer();
		GameObject::Update();
	}
	void EventManager::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void EventManager::Render()
	{
		GameObject::Render();
	}
	void EventManager::Event()
	{
		Warp* warp = object::Instantiate<Warp>(Vector3(0.0f, 0.0f, -0.01f), eLayerType::Effect);

		switch (_BossStack)
		{
		case 1:
			warp->BossType(eBossType::Sylv);
			break;
		case 2:
			warp->BossType(eBossType::Barlog);
			break;
		case 3:
			warp->BossType(eBossType::Gus);
			break;
		default:
			break;
		}
		warp->Initialize();
	}
	void EventManager::Timer()
	{
		if (_Time / 30 >= 1.0f)
		{
			_BossStack++;
			Event();
			_Time = 0;
		}
	}
	void EventManager::ButtonEvent(eIcon icon,int price)
	{
		if (MoneyCheck(price))
		{
			float a = _BarSlotCount[(UINT)icon];
			GameObject* button;
			switch (icon)
			{
			case enums::eIcon::Guppy:
				button = object::Instantiate<Guppy>(Vector3(Random(), 1.5f, a), eLayerType::Fish);
				dynamic_cast<Guppy*>(button)->SetFlag(0);
				button->Initialize();
				_BarSlotCount[(UINT)eIcon::Guppy] += 0.001f;
				break;
			case enums::eIcon::Food:
				FoodLevelUp();
				break;
			case enums::eIcon::FoodCount:
				FoodCountUp();
				break;
			case enums::eIcon::Caniboar:
				button = object::Instantiate<Caniboar>(Vector3(Random(), 1.5f, a), eLayerType::Fish);
				dynamic_cast<Caniboar*>(button)->SetFlag(0);
				button->Initialize();
				_BarSlotCount[(UINT)eIcon::Caniboar] += 0.001f;
				break;
			case enums::eIcon::Ultravore:
				button = object::Instantiate<Ultravore>(Vector3(Random(), 1.5f, a), eLayerType::Fish);
				dynamic_cast<Ultravore*>(button)->SetFlag(0);
				button->Initialize();
				_BarSlotCount[(UINT)eIcon::Ultravore] += 0.001f;
				break;
			case enums::eIcon::Egg:
				BuyEgg();
				break;
			case enums::eIcon::End:
				break;
			}
		}
	}
	void EventManager::FoodLevelUp()
	{
			Scene* scene = SceneManager::ActiveScene();
			std::vector<GameObject*> UIobj = scene->GetLayer(eLayerType::UI).GetGameObjects();
			Mouse* mouse = nullptr;
			for (auto obj : UIobj)
			{
				if (dynamic_cast<Mouse*>(obj))
				{
					mouse = dynamic_cast<Mouse*>(obj);
					break;
				}
			}
			mouse->ScriptFoodLevel();
			_FoodLevel->OnClick();
	}
	void EventManager::FoodCountUp()
	{
		Scene* scene = SceneManager::ActiveScene();
		std::vector<GameObject*> UIobj = scene->GetLayer(eLayerType::UI).GetGameObjects();
		Mouse* mouse = nullptr;
		for (auto obj : UIobj)
		{
			if (dynamic_cast<Mouse*>(obj))
			{
				mouse = dynamic_cast<Mouse*>(obj);
				break;
			}
		}
		mouse->ScriptFoodCount();
		_FoodCount->OnClick();
	}
	void EventManager::EggEvent()
	{
	}
	void EventManager::OpenButton()
	{
		switch (_EventStack)
		{
		case 0:
			FindOldGuppy();
			break;
		case 1:
			if (_EggFlag == 1)
				BuyEggOnce();
			break;
		default:
			break;
		}
	}
	void EventManager::FindOldGuppy()
	{
		Scene* scene = SceneManager::ActiveScene();
		std::vector<GameObject*> fishObj = scene->GetLayer(eLayerType::Fish).GetGameObjects();
		for (GameObject* obj : fishObj)
		{
			if (dynamic_cast<Guppy*>(obj))
			{
				if (dynamic_cast<Guppy*>(obj)->FishLevel() == 3)
				{
					_FoodLevel = object::Instantiate<InGameButton>(Vector3(-1.525f, 1.56f, -0.001f), eLayerType::UI);
					_FoodLevel->SetIcon(eIcon::Food);
					_FoodLevel->Initialize();

					_FoodCount = object::Instantiate<InGameButton>(Vector3(-1.1f, 1.56f, -0.001f), eLayerType::UI);
					_FoodCount->SetIcon(eIcon::FoodCount);
					_FoodCount->Initialize();
					
					_CaniboarButton = object::Instantiate<InGameButton>(Vector3(-0.55, 1.56, -0.001f), eLayerType::UI);
					_CaniboarButton->SetIcon(eIcon::Caniboar);
					_CaniboarButton->Initialize();
					
					_EventStack++;
					break;
				}
			}
		}
	}
	bool EventManager::MoneyCheck(int money)
	{
		Scene* scene = SceneManager::ActiveScene();
		std::vector<GameObject*> moneyObj = scene->GetLayer(eLayerType::UI).GetGameObjects();
		for (auto obj : moneyObj)
		{
			if (dynamic_cast<Money*>(obj))
			{
				if (dynamic_cast<Money*>(obj)->UseableMoney(money))
				{
					dynamic_cast<Money*>(obj)->UseMoney(money);
					return true;
				}
				return false;
			}
		}
	}
	void EventManager::BuyEggOnce()
	{
		_EggFlag++;
		_UltravoreButton = object::Instantiate<InGameButton>(Vector3(-0.005f, 1.56, -0.001f), eLayerType::UI);
		_UltravoreButton->SetIcon(eIcon::Ultravore);
		_UltravoreButton->Initialize();
	}
	void EventManager::BuyEgg()
	{
		if(_EggFlag==0)
			_EggFlag++;
		_EggButton->OnClick();
	}
	float EventManager::Random()
	{
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_real_distribution<> dis(-1.5, 1.5);
		return dis(gen);
	}
}
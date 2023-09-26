#include "MnEventManager.h"

#include <random>

#include "MnTime.h"
#include "MnWarp.h"
#include "MnObject.h"
#include "MnMouse.h"

#include "MnGuppy.h"
#include "MnInGameButton.h"

namespace Mn
{
	EventManager::EventManager()
		: _Time(0.0f)
		, _EventStack(0)
		, _BarSlotCount()
	{
	}
	EventManager::~EventManager()
	{
	}
	void EventManager::Initialize()
	{
		_BarSlotCount.resize(7,0.000001f);

		InGameButton* IGBGuppy = object::Instantiate<InGameButton>(Vector3(-2.035f, 1.56f, -0.001f), eLayerType::UI);
		IGBGuppy->SetIcon(eIcon::Guppy);
		IGBGuppy->Initialize();

		InGameButton* IGBEgg = object::Instantiate<InGameButton>(Vector3(1.085f, 1.56f, -0.001f), eLayerType::UI);
		IGBEgg->SetIcon(eIcon::Egg);
		IGBEgg->Initialize();

	}
	void EventManager::Update()
	{
		_Time += Time::DeltaTime();
		Timer();
		GameObject::Update();
	}
	void EventManager::LateUpdate()
	{
	}
	void EventManager::Render()
	{
	}
	void EventManager::Event()
	{
		Warp* warp = object::Instantiate<Warp>(Vector3(0.0f, 0.0f, -0.01f), eLayerType::Effect);

		switch (_EventStack)
		{
		case 1:
			warp->BossType(eBossType::Barlog);
			break;
		default:
			break;
		}
		warp->Initialize();
	}
	void EventManager::Timer()
	{
		if (_Time / 60 >= 1.0f)
		{
			_EventStack++;
			Event();
			_Time = 0;
		}
	}
	void EventManager::ButtonEvent(eIcon icon)
	{
		float a = _BarSlotCount[(UINT)icon];
		GameObject* button;
		switch (icon)
		{
		case enums::eIcon::Guppy:
			button = object::Instantiate<Guppy>(Vector3(Random(), 1.5f , a ),eLayerType::Fish);
			button->Initialize();
			_BarSlotCount[(UINT)eIcon::Guppy] += 0.001f;
			break;
		case enums::eIcon::Food:
			FoodLevelUp();
			break;
		case enums::eIcon::FoodCount:
			FoodCountUp();
			break;
		case enums::eIcon::Egg:
			break;
		case enums::eIcon::End:
			break;
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
	}
	void EventManager::EggEvent()
	{
	}
	float EventManager::Random()
	{
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_real_distribution<> dis(-1.5, 1.5);
		return dis(gen);
	}
}
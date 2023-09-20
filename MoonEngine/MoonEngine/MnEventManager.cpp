#include "MnEventManager.h"
#include "MnTime.h"
#include "MnWarp.h"
#include "MnObject.h"

namespace Mn
{
	EventManager::EventManager()
		: _Time(0.0f)
		, _EventStack(0)
	{
	}
	EventManager::~EventManager()
	{
	}
	void EventManager::Initialize()
	{
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
}
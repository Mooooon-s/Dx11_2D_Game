#include "MnAnimator.h"

namespace Mn
{
	Animator::Animator()
		:Component(enums::eComponentType::Animator)
	{
	}
	Animator::~Animator()
	{
		for (auto& iter : _Animations)
		{
			delete iter.second;
			iter.second = nullptr;
		}


		for (auto& iter : _Events)
		{
			delete iter.second;
			iter.second = nullptr;
		}
	}
	void Animator::Initialize()
	{
	}
	void Animator::Update()
	{
		if (_ActiveAnimation == nullptr)
			return;

		if (_ActiveAnimation->IsComplete() && _Loop)
		{
			Events* events
				= FindEvents(_ActiveAnimation->Key());
			if (events)
				events->completeEvent();

			_ActiveAnimation->Reset();
		}

		_ActiveAnimation->LateUpdate();
	}
	void Animator::LateUpdate()
	{
	}
	void Animator::Render()
	{
	}
	void Animator::Create(const std::wstring& name
		, std::shared_ptr<graphics::Texture> atlas
		, Vector2 leftTop
		, Vector2 size
		, UINT columLength
		, Vector2 offset
		, float duration)
	{
		Animation* animation = FindAnimation(name);
		if (nullptr != animation)
			return;

		animation = new Animation();
		animation->Key(name);

		animation->Create(name, atlas, leftTop, size, columLength, offset, duration);

		_Animations.insert(std::make_pair(name, animation));

		Events* events = FindEvents(name);
		if (events != nullptr)
			return;

		events = new Events();
		_Events.insert(std::make_pair(name, events));

	}
	void Animator::Create(const std::wstring& name, std::shared_ptr<graphics::Texture> atlas, std::shared_ptr<graphics::Texture> atlasAlpha, Vector2 leftTop, Vector2 size, UINT columLength, Vector2 offset, float duration)
	{
		Animation* animation = FindAnimation(name);
		if (nullptr != animation)
			return;

		animation = new Animation();
		animation->Key(name);

		animation->Create(name, atlas, atlasAlpha, leftTop, size, columLength, offset, duration);

		_Animations.insert(std::make_pair(name, animation));

		Events* events = FindEvents(name);
		if (events != nullptr)
			return;

		events = new Events();
		_Events.insert(std::make_pair(name, events));
	}
	Animation* Animator::FindAnimation(const std::wstring& name)
	{
		std::map<std::wstring, Animation*>::iterator iter 
			= _Animations.find(name);

		if (iter == _Animations.end())
			return nullptr;

		return iter->second;
	}
	Animator::Events* Animator::FindEvents(const std::wstring& name)
	{
		std::map<std::wstring, Events*>::iterator iter
			= _Events.find(name);

		if (iter == _Events.end())
			return nullptr;

		return iter->second;
	}
	void Animator::PlayAnimation(const std::wstring& name, bool loop)
	{
		Animation* prevAnimation = _ActiveAnimation;

		Events* events;
		if (prevAnimation != nullptr)
		{

			events = FindEvents(prevAnimation->Key());
			if (events)
				events->endEvent();
		}

		Animation* animation = FindAnimation(name);
		if (animation)
		{
			_ActiveAnimation = animation;
		}

		events = FindEvents(_ActiveAnimation->Key());
		if (events)
			events->startEvent();

		_Loop = loop;
		_ActiveAnimation->Reset();
	}
	void Animator::Binds()
	{
		if (_ActiveAnimation == nullptr)
			return;

		_ActiveAnimation->Binds();
	}
	std::function<void()>& Animator::StartEvent(const std::wstring key)
	{
		Events* events = FindEvents(key);

		return events->startEvent._Event;
	}
	std::function<void()>& Animator::CompleteEvent(const std::wstring key)
	{
		Events* events = FindEvents(key);

		return events->completeEvent._Event;
	}
	std::function<void()>& Animator::EndEvent(const std::wstring key)
	{
		Events* events = FindEvents(key);

		return events->endEvent._Event;
	}
}
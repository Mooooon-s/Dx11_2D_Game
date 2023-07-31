#pragma once
#include "MnComponent.h"
#include "MnAnimation.h"

namespace Mn
{

	class Animator : public Component
	{
	public:
		struct Event
		{
			void operator=(std::function<void()> func)
			{
				_Event = std::move(func);
			}

			void operator()()
			{
				if (_Event)
					_Event();
			}

			std::function<void()> _Event;
		};

		struct Events
		{
			Event startEvent;
			Event completeEvent;
			Event endEvent;
		};
		
	public:
		Animator();
		~Animator();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();

		void Create(const std::wstring& name
			, std::shared_ptr<graphics::Texture> atlas
			, Vector2 leftTop
			, Vector2 size
			, UINT columLength
			, Vector2 offset = Vector2::Zero
			, float duration = 0.1f);

		void Create(const std::wstring& name
			, std::shared_ptr<graphics::Texture> atlas
			, std::shared_ptr<graphics::Texture> atlasAlpha
			, Vector2 leftTop
			, Vector2 size
			, UINT columLength
			, Vector2 offset = Vector2::Zero
			, float duration = 0.1f);

		void CreateReverse(const std::wstring& name
			, std::shared_ptr<graphics::Texture> atlas
			, std::shared_ptr<graphics::Texture> atlasAlpha
			, Vector2 leftTop
			, Vector2 size
			, UINT columLength
			, Vector2 offset = Vector2::Zero
			, float duration = 0.1f);

		Animation* FindAnimation(const std::wstring& name);
		Events* FindEvents(const std::wstring& name);
		void PlayAnimation(const std::wstring& name, bool loop);
		void Binds();

		std::function<void()>& StartEvent(const std::wstring key);
		std::function<void()>& CompleteEvent(const std::wstring key);
		std::function<void()>& EndEvent(const std::wstring key);

		bool AnimationComplete() { return _ActiveAnimation->IsComplete(); }

	private:
		std::map<std::wstring, Animation*> _Animations;
		std::map<std::wstring, Events*> _Events;
		Animation* _ActiveAnimation;
		bool _Loop;
	};

}
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
			Event CompleteEvent;
			Event EndEvent;
		};

	private:
		std::map<std::wstring, Animation*> _Animations;
		std::map<std::wstring, Events*> _Events;

		Animation* _ActiveAnimation;
		
	public:
		Animator();
		~Animator();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();

		void Create(std::wstring name, std::shared_ptr<graphics::Texture> atlas, Vector2 leftTop, Vector2 size, UINT columLength, Vector2 offset = Vector2::Zero, float duration = 0.0f);
	};

}
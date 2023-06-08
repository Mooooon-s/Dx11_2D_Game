#pragma once
#include "MnEntity.h"
#include "MnComponent.h"
namespace Mn
{
	class GameObject : public Entity
	{
	public:
		enum eState
		{
			Active,
			Paused,
			Dead,
		};
	private:
		eState _State;
	public:
		GameObject();
		virtual ~GameObject();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();
	};
}


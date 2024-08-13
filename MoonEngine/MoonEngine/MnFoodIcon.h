#pragma once
#include "MnGameObject.h"

namespace Mn
{
	class FoodIcon : public GameObject
	{
	public:
		FoodIcon();
		~FoodIcon();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();
		virtual void OnClick();
		virtual void SoundPlay();
	private:
		int _FoodLevel;
	};
}

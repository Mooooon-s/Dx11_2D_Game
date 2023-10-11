#pragma once
#include "MnGameObject.h"
namespace Mn
{
	class FoodLevelIcon : public GameObject
	{
	public:
		FoodLevelIcon();
		~FoodLevelIcon();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();
		virtual void FontRender();
		virtual void OnClick();
	private:
		UINT _Count;
		wchar_t _szFloat[50];
	};
}

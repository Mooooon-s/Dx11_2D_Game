#pragma once
#include "MnGameObject.h"

namespace Mn
{
	class PriceTag : public GameObject
	{
	public:
		PriceTag();
		~PriceTag();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();
		virtual void FontRender();
	public:
		void SetPosition();
	public:
		void SetPrice(int money) { _Money = money; }
		void SetIcon(eIcon icon) { _Icon = icon; }
	private:
		wchar_t _szFloat[50];
		Vector2 _Pos;
		eIcon _Icon;
		int _Money;
	};
}

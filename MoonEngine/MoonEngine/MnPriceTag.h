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
	public:
		void TagOff() { _On = false; }
		void TagOn() { _On = true; }
		void TagOnOff(bool _onoff) { _On = _onoff; }
	private:
		wchar_t _szFloat[50];
		Vector2 _Pos;
		eIcon _Icon;
		bool _On;
		int _Money;
	};
}

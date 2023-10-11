#include "MnMoney.h"
#include "MnFontWrapper.h"

namespace Mn
{
	Money::Money()
		: _Money(400)
		, _szFloat(L"000")
	{
	}
	Money::~Money()
	{
		FontWrapper::Release();
	}
	void Money::Initialize()
	{
		FontWrapper::Initialize();
		GameObject::Initialize();
	}
	void Money::Update()
	{
		GameObject::Update();
	}
	void Money::LateUpdate()
	{
		swprintf_s(_szFloat, 50, L"%d", (UINT)_Money);
		GameObject::LateUpdate();
	}
	void Money::Render()
	{
		GameObject::Render();
	}
	void Money::FontRender()
	{
		FontWrapper::DrawFont(_szFloat, 825, 60, 25, FONT_RGBA(255, 0, 255, 255));
	}
	void Money::OnClick()
	{
	}
	void Money::EarnMoney(int money)
	{
		_Money += money;
	}
	void Money::UseMoney(int money)
	{
		_Money -= money;
	}
	bool Money::UseableMoney(int money)
	{
		if(_Money-money < 0)
			return false;
		return true;
	}
}
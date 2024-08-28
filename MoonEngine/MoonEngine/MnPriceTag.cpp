#include "MnPriceTag.h"
#include "MnFontWrapper.h"

namespace Mn
{
	PriceTag::PriceTag()
		: _Money(0)
		, _szFloat(L"000")
		, _Pos(Vector2::Zero)
		, _On(true)
	{
	}
	PriceTag::~PriceTag()
	{
	}
	void PriceTag::Initialize()
	{
		swprintf_s(_szFloat, 50, L"$%d", (UINT)_Money);
	}
	void PriceTag::Update()
	{
		GameObject::Update();
	}
	void PriceTag::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void PriceTag::Render()
	{
		GameObject::Render();
	}
	void PriceTag::FontRender()
	{
		if(_On)
			FontWrapper::DrawFont(_szFloat, (int)_Pos.x, (int)_Pos.y, 16, FONT_RGBA(255, 0, 255, 255));
		GameObject::FontRender();
	}
	void PriceTag::SetPosition()
	{
		switch (_Icon)
		{
		case Mn::enums::eIcon::Guppy:
			_Pos = Vector2(60, 70);
			break;
		case Mn::enums::eIcon::Food:
			_Pos = Vector2(160, 70);
			break;
		case Mn::enums::eIcon::FoodCount:
			_Pos = Vector2(240, 70);
			break;
		case Mn::enums::eIcon::Caniboar:
			_Pos = Vector2(350, 70);
			break;
		case Mn::enums::eIcon::Ultravore:
			_Pos = Vector2(450, 70);
			break;
		case Mn::enums::eIcon::Weapon:
			break;
		case Mn::enums::eIcon::Egg:
			_Pos = Vector2(675, 70);
			break;
		case Mn::enums::eIcon::End:
			break;
		default:
			break;
		}
	}
}
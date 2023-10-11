#include "MnFoodLevelIcon.h"
#include "MnFontWrapper.h"

namespace Mn
{
	FoodLevelIcon::FoodLevelIcon()
		: _Count(3)
		, _szFloat(L"3")
	{
	}
	FoodLevelIcon::~FoodLevelIcon()
	{
	}
	void FoodLevelIcon::Initialize()
	{
	}
	void FoodLevelIcon::Update()
	{
	}
	void FoodLevelIcon::LateUpdate()
	{
		swprintf_s(_szFloat, 50, L"%d", (UINT)_Count);
	}
	void FoodLevelIcon::Render()
	{
	}
	void FoodLevelIcon::FontRender()
	{
		FontWrapper::DrawFont(_szFloat, 250, 25, 25, FONT_RGBA(255, 0, 255, 255));
	}
	void FoodLevelIcon::OnClick()
	{
		if (_Count < 5)
			_Count++;
	}
}
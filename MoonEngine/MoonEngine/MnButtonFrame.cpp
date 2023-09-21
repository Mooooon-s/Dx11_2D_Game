#include "MnButtonFrame.h"
#include "MnButtonFrameRender.h"

namespace Mn
{
	ButtonFrame::ButtonFrame()
	{
	}
	ButtonFrame::~ButtonFrame()
	{
	}
	void ButtonFrame::Initialize()
	{
		ButtonFrameRender* BFR = AddComponent<ButtonFrameRender>();
		BFR->Initialize();
	}
	void ButtonFrame::Update()
	{
		GameObject::Update();
	}
	void ButtonFrame::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void ButtonFrame::Render()
	{
		GameObject::Render();
	}
}
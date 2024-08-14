#pragma once
#include "MnButton.h"

namespace Mn {
	class StartButtonBarRender : public Button
	{
	public:
		StartButtonBarRender();
		~StartButtonBarRender();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;
		virtual void FontRender() override;
		virtual void OnClick() override;
		virtual void OnClick(Vector3 pos) override;
		virtual void MouseOn() override;
		virtual void MouseOff() override;
	private:
	};

}



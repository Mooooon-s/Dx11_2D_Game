#pragma once
#include "MnGameObject.h"

namespace Mn
{
	class ButtonPanel : public GameObject
	{
	public:
		ButtonPanel();
		~ButtonPanel();

		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render() override;
		void OnClick() override;
		void MouseOn() override;
		void MouseOff() override;
	private:
	};
}

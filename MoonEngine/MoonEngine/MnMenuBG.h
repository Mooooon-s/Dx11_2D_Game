#pragma once
#include "MnBackGround.h"

namespace Mn
{

	class MenuBG : public BackGround
	{
	public:
		MenuBG();
		~MenuBG();

		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render() override;
	private:
	};

}
#pragma once
#include "MnGameObject.h"

namespace Mn
{

	class Money : public GameObject
	{
	public:
		Money();
		~Money();

		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render() override;
		void FontRender() override;
		void OnClick() override;
	public:
		void EarnMoney(UINT money);
	private:
		UINT _Money;
		wchar_t _szFloat[50];
	};

}
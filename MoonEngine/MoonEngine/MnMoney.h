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
		void EarnMoney(int money);
		void UseMoney(int money);
		bool UseableMoney(int money);
	private:
		int _Money;
		wchar_t _szFloat[50];
	};

}
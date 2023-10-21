#pragma once
#include "MnGameObject.h"
namespace Mn
{
	class InGameButton;
	class EventManager : public GameObject
	{
	public:
		EventManager();
		~EventManager();

		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render() override;
		void FontRender() override;

	public:
		void Event();
		void Timer();
		float Random();
		void ButtonEvent(eIcon icon, int money);
		void FoodLevelUp();
		void FoodCountUp();
		void EggEvent();
		void OpenButton();
		void FindOldGuppy();
		bool MoneyCheck(int money);
		void BuyEggOnce();
		void BuyEgg();
		void EggCrack();
	private:
		std::vector<float> _BarSlotCount;
		wchar_t _SzString[100];
		float _Time;
		int _EventStack;
		int _WaringFlag;
		int _BossStack;
		int _EggFlag;
		int _EggStack;
		int _Level;
		std::wstring _WaringSantance;
		InGameButton* _FoodLevel;
		InGameButton* _FoodCount;
		InGameButton* _CaniboarButton;
		InGameButton* _UltravoreButton;
		InGameButton* _EggButton;
	};
}

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
	public:
		void Event();
		void Timer();
		float Random();
		void ButtonEvent(eIcon icon);
		void FoodLevelUp();
		void FoodCountUp();
		void EggEvent();
		void OpenButton();
		void FindOldGuppy();
	private:
		std::vector<float> _BarSlotCount;
		float _Time;
		int _EventStack;
		int _BossStack;
		InGameButton* _FoodLevel;
	};
}

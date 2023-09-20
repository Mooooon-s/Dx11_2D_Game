#pragma once
#include "MnGameObject.h"
namespace Mn
{
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
	private:
		float _Time;
		int _EventStack;
	};
}

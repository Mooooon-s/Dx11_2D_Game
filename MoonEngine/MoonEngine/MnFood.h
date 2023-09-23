#pragma once
#include "../Engine_SOURCE/MnGameObject.h"

namespace Mn
{
	class Food : public GameObject
	{
	public:
		Food();
		~Food();

		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render() override;
		void OnClick() override;
	public:
		void FoodLevel(int level) { _Level = level; }
	private:
		int _Level;
	};
}
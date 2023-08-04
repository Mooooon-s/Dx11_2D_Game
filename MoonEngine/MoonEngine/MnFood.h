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
	public:

	private:
		int _Level;
	};
}
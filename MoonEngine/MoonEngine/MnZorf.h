#pragma once
#include "MnGameObject.h"

namespace Mn
{
	class Zorf : public GameObject
	{
	public:
		Zorf();
		~Zorf();

		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render() override;
	private:
	};
}

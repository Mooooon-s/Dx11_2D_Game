#pragma once
#include "MnGameObject.h"

namespace Mn
{

	class Stinky : public GameObject
	{
	public:
		Stinky();
		~Stinky();

		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render() override;
	private:

	};

}
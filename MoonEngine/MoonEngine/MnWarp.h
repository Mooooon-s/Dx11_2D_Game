#pragma once
#include "MnGameObject.h"

namespace Mn
{
	class Warp : public GameObject
	{
	public:
		Warp();
		~Warp();

		 void Initialize() override;
		 void Update() override;
		 void LateUpdate() override;
		 void Render() override;
	private:

	};
}

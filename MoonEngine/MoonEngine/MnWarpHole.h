#pragma once
#include "MnGameObject.h"

namespace Mn
{
	class WarpHole : public GameObject
	{
	public:
		WarpHole();
		~WarpHole();

		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render() override;
	private:
		float _Time;
		bool _Flag;
	};

}
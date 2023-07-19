#pragma once
#include "MnBackGround.h"

namespace Mn
{

	class ForestLight : public BackGround
	{
	public:
		ForestLight();
		~ForestLight();

		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render() override;
	};

}
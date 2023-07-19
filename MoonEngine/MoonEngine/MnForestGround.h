#pragma once
#include "MnBackGround.h"

namespace Mn
{

	class ForestGround : public BackGround
	{
	public:
		ForestGround();
		~ForestGround();

		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render() override;
	};

}

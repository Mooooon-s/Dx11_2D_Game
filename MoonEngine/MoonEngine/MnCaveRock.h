#pragma once
#include "MnBackGround.h"

namespace Mn
{
	class CaveRock : public BackGround
	{
	public:
		CaveRock();
		~CaveRock();

		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render() override;
	};

}
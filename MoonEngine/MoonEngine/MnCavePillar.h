#pragma once
#include "MnBackGround.h"

namespace Mn
{

	class CavePillar : public BackGround
	{
	public:
		CavePillar();
		~CavePillar();

		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render() override;
	};

}
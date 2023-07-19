#pragma once
#include "MnBackGround.h"
namespace Mn
{

	class CaveBossBG : public BackGround
	{
	public:
		CaveBossBG();
		~CaveBossBG();

		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render() override;
	};

}
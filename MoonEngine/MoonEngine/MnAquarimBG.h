#pragma once
#include "MnBackGround.h"

namespace Mn
{

	class AquarimBG : public BackGround
	{
	public:
		AquarimBG(eAquarim stage);
		~AquarimBG();

		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render() override;

		std::wstring StageName();
	private:
		eAquarim _Stage;
		std::wstring _StageName;
	};

}
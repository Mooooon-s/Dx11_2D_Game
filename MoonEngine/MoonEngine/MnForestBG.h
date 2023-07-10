#pragma once
#include "MnBackGround.h"

namespace Mn
{
	class ForestBG : public BackGround
	{
	private:

	public:
		ForestBG();
		~ForestBG();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;
	};

}
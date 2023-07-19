#pragma once
#include "MnBackGround.h"

namespace Mn
{

	class ForestTree : public BackGround
	{
	public:
		ForestTree();
		~ForestTree();

		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render() override;
	};

}
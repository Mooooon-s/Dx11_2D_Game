#pragma once
#include "MnSceneManager.h"

namespace Mn
{

	class CaveBG
	{
	private:
		Scene* _Scene;
	public:
		CaveBG(Scene* scene);
		~CaveBG();

		void Initialize();
	};

}
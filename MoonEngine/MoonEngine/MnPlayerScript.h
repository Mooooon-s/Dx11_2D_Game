#pragma once
#include "../Engine_SOURCE/MnScript.h"

namespace Mn
{

	class PlayerScript : public Script
	{
	public:
		PlayerScript();
		~PlayerScript();

		virtual void Update() override;
	};
}

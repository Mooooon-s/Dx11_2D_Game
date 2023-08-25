#pragma once
#include "MnScript.h"

namespace Mn
{
	class PearlScript : public Script
	{
	public:
		PearlScript();
		~PearlScript();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;
	private:

	};

}
#pragma once
#include "MnScript.h"

namespace Mn
{
	class SparkScript : public Script
	{
	public:
		SparkScript();
		~SparkScript();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;
	private:
	};
}

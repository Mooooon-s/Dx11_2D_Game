#pragma once
#include "MnScript.h"

namespace Mn
{
	class SparkRender : public Script
	{
	public:
		SparkRender();
		~SparkRender();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;
	private:

	};
}

#pragma once
#include "MnScript.h"
#include "MnGameObject.h"

namespace Mn
{
	class DiamondScript : public Script
	{
	public:
		DiamondScript();
		~DiamondScript();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;
	private:
		float _Speed;
		float _Time;
	};
}

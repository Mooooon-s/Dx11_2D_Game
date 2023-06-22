#pragma once
#include "MnComponent.h"

namespace Mn
{

	class Script : public Component
	{
	private:

	public:
		Script();
		~Script();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;
	};

}

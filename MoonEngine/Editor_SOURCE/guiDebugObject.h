#pragma once
#include "../Engine_SOURCE/MnGameObject.h"

namespace gui
{
	class DebugObject : public Mn::GameObject
	{
	public:
		DebugObject();
		~DebugObject();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;
	};

}
#pragma once
#include "../Engine_SOURCE/MnScript.h"
#include "../Engine_SOURCE/MnCamera.h"

namespace Mn
{

	class GridScript : public Script
	{
	private:
		Camera* _Camera;
	public:
		GridScript();
		~GridScript();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		void SetCamera(Camera* camera) { _Camera = camera; }
	};
}

#pragma once
#include "../Engine_SOURCE/MnScene.h"

namespace Mn
{

	class MountainStage : public Scene
	{
	public:
		MountainStage();
		~MountainStage();

		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render() override;
		void Destroy() override;

		void OnEnter() override;
		void OnExit() override;
	};

}
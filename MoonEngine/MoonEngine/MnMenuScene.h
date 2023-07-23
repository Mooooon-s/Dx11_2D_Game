#pragma once
#include "../Engine_SOURCE/MnScene.h"

namespace Mn
{
	class MenuScene : public Scene
	{
	public:
		MenuScene();
		~MenuScene();

		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render() override;
		void OnEnter() override;
		void OnExit() override;
	private:
	};

}
#pragma once
#include "../Engine_SOURCE/MnScene.h"
#include "../Engine_SOURCE/MnKdTree.h"


namespace Mn
{

	class CaveStage : public Scene
	{
	public:
		CaveStage();
		~CaveStage();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();
		virtual void Destroy();

		virtual void OnEnter();
		virtual void OnExit();
	private:
	};

}
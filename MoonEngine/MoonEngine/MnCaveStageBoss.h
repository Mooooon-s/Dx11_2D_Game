#pragma once
#include "../Engine_SOURCE/MnScene.h"
#include "../Engine_SOURCE/MnKdTree.h"

namespace Mn
{

	class CaveStageBoss : public Scene
	{
	public:
		CaveStageBoss();
		~CaveStageBoss();

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

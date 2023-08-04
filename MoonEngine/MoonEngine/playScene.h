#pragma once
#include "../Engine_SOURCE/MnScene.h"
#include "../Engine_SOURCE/MnKdTree.h"

namespace Mn
{
	extern Mn::KdTree* kdTree;
	class playScene : public Scene
	{
	private:
		std::vector<GameObject*> _ActiveObjs;
	public:
		playScene();
		~playScene();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;
		virtual void Destroy();

		virtual void OnEnter();
		virtual void OnExit();
	};

}

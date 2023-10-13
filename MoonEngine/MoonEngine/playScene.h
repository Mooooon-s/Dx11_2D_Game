#pragma once
#include "../Engine_SOURCE/MnScene.h"
#include "../Engine_SOURCE/MnKdTree.h"

namespace Mn
{
	extern Mn::KdTree* kdTree;
	extern Mn::KdTree* GuppyTree;
	class playScene : public Scene
	{
	private:
		std::vector<GameObject*> _ActiveObjs;
		std::vector<GameObject*> _GuppyObjs;
	public:
		playScene();
		~playScene();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;
		virtual void Destroy() override;

		virtual void OnEnter();
		virtual void OnExit();
	};

}

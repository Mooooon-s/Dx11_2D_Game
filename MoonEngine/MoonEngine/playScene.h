#pragma once
//#include "MnScene.h"
#include "../Engine_SOURCE/MnScene.h"
#include "../Engine_SOURCE/MnKdTree.h"

namespace Mn
{

	class playScene : public Scene
	{
	private:
		KdTree* _KdTree;
		std::vector<GameObject*> _ActiveObjs;
	public:
		playScene();
		~playScene();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;
	};

}

#pragma once
//#include "MnScene.h"
#include "../Engine_SOURCE/MnScene.h"
namespace Mn
{

	class playScene : public Scene
	{
	private:

	public:
		playScene();
		~playScene();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;
	};

}

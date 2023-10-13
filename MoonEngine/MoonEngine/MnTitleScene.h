#pragma once
#include "../Engine_SOURCE/MnScene.h"
namespace Mn
{

	class TitleScene : public Scene
	{
	private:
	public:
		TitleScene();
		~TitleScene();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;
		virtual void Destroy() override;

		virtual void OnEnter() override;
		virtual void OnExit() override;
	};
}

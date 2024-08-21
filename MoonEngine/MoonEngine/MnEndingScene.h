#pragma once
#include "../Engine_SOURCE/MnScene.h"

namespace Mn
{
	class EndingScene : public Scene
	{
	public:
		EndingScene();
		~EndingScene();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;
		virtual void Destroy() override;

		virtual void OnEnter() override;
		virtual void OnExit() override;
		virtual void FontRender() override;

	public:
		void MakeIcon();
		void CalulatePos(GameObject* _obj);
	private:
		std::map<std::wstring, GameObject*> Obj;
		const wchar_t* _szFloat;
		GameObject* _Cam;
	};
}

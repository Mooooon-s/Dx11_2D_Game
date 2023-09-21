#pragma once
#include "MnGameObject.h"
#include "MnAnimator.h"

#include "MnEventManager.h"

namespace Mn
{
	class ButtonPanel : public GameObject
	{
	public:
		ButtonPanel();
		~ButtonPanel();

		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render() override;
		void OnClick(Vector3 pos) override;
		void MouseOn() override;
		void MouseOff() override;
	public:
		void SetIcon(eIcon icon) { _Icon = icon; }
		eIcon GetIcon() { return _Icon; }
	private:
		eIcon _Icon;
		Animator* _Animator;
		EventManager* _EventManager;
	};
}

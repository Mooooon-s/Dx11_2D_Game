#pragma once
#include "MnGameObject.h"
#include "MnAmpBehaviorTree.h"

namespace Mn
{
	class Amp : public GameObject
	{
	public:
		Amp();
		~Amp();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();
		virtual void OnClick(Vector3 pos);
	private:
		AmpBehaviorTree* _ABT;
	};
}

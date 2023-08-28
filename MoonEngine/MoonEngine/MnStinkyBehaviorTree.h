#pragma once
#include "..\Engine_SOURCE\MnScript.h"

#include "..\Engine_SOURCE\MnBlackBoard.h"

#include "MnRootNode.h"

namespace Mn
{
	class StinkyBehaviorTree : public Script
	{
	public:
		StinkyBehaviorTree();
		~StinkyBehaviorTree();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		virtual void OnCollisionEnter(Collider2D* other);
		virtual void OnCollisionStay(Collider2D* other) {};
		virtual void OnCollisionExit(Collider2D* other) {};
	private:
		RootNode* _Root;
		BlackBoard* _BlackBoard;
	};
}

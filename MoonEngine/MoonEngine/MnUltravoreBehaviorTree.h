#pragma once
#include "MnScript.h"
#include "MnBlackBoard.h"
#include "MnRootNode.h"

namespace Mn
{
	class UltravoreBehaviorTree : public Script
	{
	public:
		UltravoreBehaviorTree();
		~UltravoreBehaviorTree();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		virtual void OnCollisionEnter(Collider2D* other) override;
		virtual void OnCollisionStay(Collider2D* other) {};
		virtual void OnCollisionExit(Collider2D* other) {};
	private:
		std::shared_ptr<BlackBoard> _BlackBoard;
		RootNode* _Root;
	};
}

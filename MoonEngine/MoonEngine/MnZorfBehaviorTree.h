#pragma once
#include "MnScript.h"
#include "MnBlackBoard.h"
#include "MnRootNode.h"

namespace Mn
{
	class ZorfBehaviorTree : public Script
	{
	public:
		ZorfBehaviorTree();
		~ZorfBehaviorTree();

		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render() override;

		void OnCollisionEnter(Collider2D* other) override;
		void OnCollisionStay(Collider2D* other) override;
		void OnCollisionExit(Collider2D* other) override;
	private:
		RootNode* _Root;
		std::shared_ptr<BlackBoard> _BlackBoard;
	};
}

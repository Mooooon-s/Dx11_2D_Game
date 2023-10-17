#pragma once
#include "MnScript.h"
#include "MnBlackBoard.h"
#include "MnRootNode.h"

namespace Mn
{
	class GusBehaviorTree : public Script
	{
	public:
		GusBehaviorTree();
		~GusBehaviorTree();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		virtual void OnCollisionEnter(Collider2D* other);
	private:
		std::shared_ptr<BlackBoard> _BlackBoard;
		RootNode* _Root;
	};
}

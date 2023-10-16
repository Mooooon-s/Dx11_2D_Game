#pragma once
#include "MnScript.h"
#include "MnBlackBoard.h"
#include "MnRootNode.h"

namespace Mn
{
	class AmpBehaviorTree : public Script
	{
	public:
		AmpBehaviorTree();
		~AmpBehaviorTree();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		void OnClick();
	private:
		std::shared_ptr<BlackBoard> _BlackBoard;
		RootNode* _Root;
		int _Stack;
	};
}

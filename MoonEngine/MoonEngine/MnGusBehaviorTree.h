#pragma once
#include "MnScript.h"
#include "MnBlackBoard.h"
#include "../Engine_SOURCE/MnRootNode.h"
#include "MnGetDemaged.h"

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
		BlackBoard* _BlackBoard;
		RootNode* _Root;
		GetDemaged* _GetDemage;
	};
}

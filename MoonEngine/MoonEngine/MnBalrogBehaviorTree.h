#pragma once
#include "../Engine_SOURCE/MnRootNode.h"
#include "MnScript.h"
#include "MnGetDemaged.h"

namespace Mn
{
	class BalrogBehaviorTree : public Script
	{
	public:
		BalrogBehaviorTree();
		~BalrogBehaviorTree();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		virtual void OnCollisionEnter(Collider2D* other) override;
		virtual void OnCollisionStay(Collider2D* other) {};
		virtual void OnCollisionExit(Collider2D* other) {};

		void OnClick(Vector3 pos);
	private:
		RootNode* _Root;
		BlackBoard* _BlackBorad;
		GetDemaged* _GetDemage;
	};

}
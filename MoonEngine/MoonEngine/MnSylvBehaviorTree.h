#pragma once
#include "MnScript.h"
#include "MnRootNode.h"
#include "MnBlackBoard.h"
#include "MnGetDemaged.h"

namespace Mn
{

	class SylvBehaviorTree : public Script
	{
	public:
		SylvBehaviorTree();
		~SylvBehaviorTree();


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
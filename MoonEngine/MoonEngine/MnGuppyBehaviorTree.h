#pragma once
#include "../Engine_SOURCE/MnBlackBoard.h"
#include "../Engine_SOURCE/MnRootNode.h"
#include "../Engine_SOURCE/MnSequence.h"
#include "../Engine_SOURCE/MnSelector.h"
#include "../Engine_SOURCE/MnInverter.h"
#include "../Engine_SOURCE/MnSucceeder.h"
#include "../Engine_SOURCE/MnRepeatUntilFail.h"

#include "MnGameObject.h"
#include "MnScript.h"


namespace Mn
{
	class GuppyBehaviorTree : public Script
	{
	public:
		GuppyBehaviorTree();
		~GuppyBehaviorTree();


		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		virtual void OnCollisionEnter(Collider2D* other) override;
		virtual void OnCollisionStay(Collider2D* other) override;
		virtual void OnCollisionExit(Collider2D* other) override;

	public:
		void Run();
		UINT GetGuppyLevel();
	public:
		RootNode* _Root;
		Sequence* _Sequence;
		Selector* _Selector;
		Inverter* _Inverter;
		std::shared_ptr<BlackBoard> _BlackBoard;
	};
}
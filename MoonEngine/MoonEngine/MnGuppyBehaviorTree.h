#pragma once
#include "../Engine_SOURCE/MnBlackBoard.h"
#include "../Engine_SOURCE/MnRootNode.h"
#include "../Engine_SOURCE/MnSequence.h"
#include "../Engine_SOURCE/MnSelector.h"
#include "../Engine_SOURCE/MnInverter.h"
#include "../Engine_SOURCE/MnSucceeder.h"
#include "../Engine_SOURCE/MnRepeatUntilFail.h"

#include "MnGameObject.h"

namespace Mn
{
	class GuppyBehaviorTree
	{
	public:
		GuppyBehaviorTree();
		GuppyBehaviorTree(GameObject* guppy);
		~GuppyBehaviorTree();

		void Initialize();
		void Run();

	public:
		GameObject* _Guppy;
		RootNode* _Root;
		Sequence* _Sequence;
		Selector* _Selector;
		Inverter* _Inverter;
		std::shared_ptr<BlackBoard> _BlackBoard;
	};
}
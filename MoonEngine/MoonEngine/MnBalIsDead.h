#pragma once
#include "..\Engine_SOURCE\MnBtNode.h"
#include "..\Engine_SOURCE\MnBlackBoard.h"
namespace Mn
{
	class BalIsDead : public Node
	{
	public:
		BalIsDead();
		BalIsDead(BlackBoard* board);
		~BalIsDead();

		virtual enums::eBTState Run() override;
	private:
		BlackBoard* _BlackBoard;
	};
}

#pragma once
#include "..\Engine_SOURCE\MnBtNode.h"
#include "..\Engine_SOURCE\MnBlackBoard.h"
namespace Mn
{
	class MonIsDead : public Node
	{
	public:
		MonIsDead();
		MonIsDead(BlackBoard* board);
		~MonIsDead();

		virtual enums::eBTState Run() override;
	private:
		BlackBoard* _BlackBoard;
	};
}

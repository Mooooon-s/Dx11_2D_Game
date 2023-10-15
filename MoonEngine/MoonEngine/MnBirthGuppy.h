#pragma once
#include "MnBtNode.h"
#include "MnBlackBoard.h"

namespace Mn
{
	class BirthGuppy : public Node
	{
	public:
		BirthGuppy();
		BirthGuppy(BlackBoard* board);
		~BirthGuppy();

		enums::eBTState Run() override;
	private:
		BlackBoard* _BlackBoard;
		float _ZPosition;
	};
}

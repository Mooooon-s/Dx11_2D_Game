#pragma once
#include "MnBtNode.h"
#include "MnBlackBoard.h"

namespace Mn
{
	class Swim : public Node
	{
	public:
		Swim();
		Swim(BlackBoard* board);
		~Swim();

		enums::eBTState Run() override;
	private:
		BlackBoard* _BlackBoard;
		float _Speed;
	};
}

#pragma once
#include "MnBtNode.h"
#include "MnBlackBoard.h"

namespace Mn
{
	class Rush2Boss : public Node
	{
	public:
		Rush2Boss();
		Rush2Boss(BlackBoard* board);
		~Rush2Boss();

		enums::eBTState Run() override;
	public:
		void Rush();
	private:
		BlackBoard* _BlackBoard;
		float _Time;
	};
}

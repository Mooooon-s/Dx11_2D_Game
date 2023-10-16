#pragma once
#include "MnBtNode.h"
#include "MnBlackBoard.h"

namespace Mn
{
	class ShockWave : public Node
	{
	public:
		ShockWave();
		ShockWave(BlackBoard* board);
		~ShockWave();

		enums::eBTState Run() override;
	public:
		BlackBoard* _BlackBoard;
	};
}

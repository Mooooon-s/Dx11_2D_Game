#pragma once
#include "MnBtNode.h"
#include "MnBlackBoard.h"

namespace Mn
{
	class BossStun : public Node
	{
	public:
		BossStun();
		BossStun(BlackBoard* board);
		~BossStun();

		enums::eBTState Run() override;
	private:
		float _Time;
		BlackBoard* _BlackBoard;
	};
}

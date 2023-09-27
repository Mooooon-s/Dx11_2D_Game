#pragma once
#include "MnBtNode.h"
#include "MnBlackBoard.h"

namespace Mn
{
	class FishTurn : public Node
	{
	public:
		FishTurn();
		FishTurn(BlackBoard* board);
		~FishTurn();

		enums::eBTState Run() override;
	public:
		void AnimationPlay();
	private:
		BlackBoard* _BlackBoard;
	};
}

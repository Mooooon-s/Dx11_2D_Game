#pragma once
#include "MnBtNode.h"
#include "MnBlackBoard.h"

namespace Mn
{
	class IsDeath : public Node
	{
	public:
		IsDeath();
		IsDeath(BlackBoard* board);
		~IsDeath();

		enums::eBTState Run() override;

	public:
		void AnimationPlay();
	private:
		BlackBoard* _BlackBoard;
		int _Flag;
	};
}

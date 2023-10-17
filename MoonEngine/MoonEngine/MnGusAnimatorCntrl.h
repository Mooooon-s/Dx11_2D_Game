#pragma once
#include "MnBtNode.h"
#include "MnBlackBoard.h"

namespace Mn
{
	class GusAnimatorCntrl : public Node
	{
	public:
		GusAnimatorCntrl();
		GusAnimatorCntrl(BlackBoard* board);
		~GusAnimatorCntrl();

		enums::eBTState Run();
	public:
		void PlayAnimation();
	private:
		BlackBoard* _BlackBoard;
		enums::eDir _Dir;
	};
}

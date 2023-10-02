#pragma once
#include "MnBtNode.h"
#include "MnBlackBoard.h"

namespace Mn
{
	class ZorfAnimationCntrl : public Node
	{
	public:
		ZorfAnimationCntrl();
		ZorfAnimationCntrl(BlackBoard* board);
		~ZorfAnimationCntrl();

		enums::eBTState Run() override;
	public:
		void PlayAnimation(enums::eBehavior behavior);
	private:
		BlackBoard* _BlackBoard;
		eFishState	_State;
		eBehavior	_Behavior;
	};
}

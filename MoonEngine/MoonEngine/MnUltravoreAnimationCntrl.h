#pragma once
#include "MnBtNode.h"
#include "MnBlackBoard.h"

namespace Mn
{
	class UltravoreAnimationCntrl : public Node
	{
	public:
		UltravoreAnimationCntrl();
		UltravoreAnimationCntrl(BlackBoard* board);
		~UltravoreAnimationCntrl();

		enums::eBTState Run() override;
	public:
		void PlayAnimation(enums::eBehavior behavior);
		void FullAnimation(enums::eBehavior behavior);
		void DeathAnimation();
		void afterAction();
	private:
		BlackBoard* _BlackBoard;
		eBehavior _Behavior;
		eFishState _State;
	};
}

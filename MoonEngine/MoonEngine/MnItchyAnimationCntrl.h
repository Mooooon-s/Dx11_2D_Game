#pragma once
#include "MnBtNode.h"
#include "MnBlackBoard.h"

namespace Mn
{
	class ItchyAnimationCntrl : public Node
	{
	public:
		ItchyAnimationCntrl();
		ItchyAnimationCntrl(BlackBoard* board);
		~ItchyAnimationCntrl();

		enums::eBTState Run() override;
	public:
		void PlayAnimation(enums::eBehavior behavior);
		void AttackAnimation(enums::eBehavior behavior);
		void IdleAnimation(enums::eBehavior behavior);
	private:
		BlackBoard* _BlackBoard;
		enums::eBehavior _Behavior;
		enums::eFishState _State;
	};
}

#pragma once
#include "MnBtNode.h"
#include "MnBlackBoard.h"

namespace Mn
{
	class AmpAnimationCntrl : public Node
	{
	public:
		AmpAnimationCntrl();
		AmpAnimationCntrl(BlackBoard* board);
		~AmpAnimationCntrl();

		enums::eBTState Run() override;
	public:
		void PlayAnimation(enums::eBehavior behavior);
		void ChargedAnimation(enums::eBehavior behavior);
		void IdleAnimation(enums::eBehavior behavior);

	private:
		BlackBoard* _BlackBoard;
		enums::eFishState _State;
		enums::eBehavior _Behavior;
		bool _Charged;
	};
}

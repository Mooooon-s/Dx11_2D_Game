#pragma once
#include "MnBtNode.h"
#include "MnBlackBoard.h"

namespace Mn
{
	class PregoAnimationCntrl : public Node
	{
	public:
		PregoAnimationCntrl();
		PregoAnimationCntrl(BlackBoard* board);
		~PregoAnimationCntrl();

		enums::eBTState Run();
	public:
		void PlayAnimation(enums::eBehavior behavior);
		void PregMentAnimation(enums::eBehavior behavior);
		void IdleAnimation(enums::eBehavior behavior);
		void GetPregMent();
		void EndPregMent();
	private:
		BlackBoard* _BlackBoard;
		enums::eBehavior _Behavior;
		enums::eFishState _State;
	};
}

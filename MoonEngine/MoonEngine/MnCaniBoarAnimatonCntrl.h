#pragma once
#include "MnBtNode.h"
#include "MnBlackBoard.h"
namespace Mn
{
	class CaniBoarAnimatonCntrl : public Node
	{
	public:
		CaniBoarAnimatonCntrl();
		CaniBoarAnimatonCntrl(BlackBoard* board);
		~CaniBoarAnimatonCntrl();

		virtual enums::eBTState Run() override;
	public:
		void PlayAnimation(enums::eBehavior behavior);
		void FullAnimation(enums::eBehavior behavior);
		void StarvingAnimation(enums::eBehavior behavior);
		void DeathAnimation();
		void afterAction();
	private:
		BlackBoard* _BlackBoard;
		eFishState _State;
		eBehavior _Behavior;
	};
}

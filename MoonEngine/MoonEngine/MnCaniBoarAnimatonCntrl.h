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
	private:
		BlackBoard* _BlackBoard;
	};
}

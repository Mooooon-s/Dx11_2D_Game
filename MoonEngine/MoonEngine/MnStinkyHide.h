#pragma once
#include "MnBtNode.h"
#include "MnBlackBoard.h"
namespace Mn
{
	class StinkyHide : public Node
	{
	public:
		StinkyHide();
		StinkyHide(BlackBoard* board);
		~StinkyHide();

		enums::eBTState Run() override;
	private:
		BlackBoard* _BlackBoard;
	};
}

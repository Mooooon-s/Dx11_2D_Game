#pragma once
#include "../Engine_SOURCE/MnBtNode.h"
#include "../Engine_SOURCE/MnBlackBoard.h"


namespace Mn
{

	class Move2Food : public Node
	{
	public:
		Move2Food();
		Move2Food(BlackBoard* board);
		~Move2Food();

		virtual enums::eBTState Run() override;
	private:
		BlackBoard* _BlackBoard;
		enums::eDir _Dir;
		int _Flag;
	};

}
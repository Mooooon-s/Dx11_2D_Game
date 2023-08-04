#pragma once
#include "../Engine_SOURCE/MnBtNode.h"
#include "../Engine_SOURCE/MnBlackBoard.h"

namespace Mn
{
	class AddHungryStack : public Node
	{
	public:
		AddHungryStack();
		AddHungryStack(BlackBoard* board);
		~AddHungryStack();

		virtual enums::eBTState Run() override;
	private:
		float _Time;
		BlackBoard* _BlackBoard;
	};

}
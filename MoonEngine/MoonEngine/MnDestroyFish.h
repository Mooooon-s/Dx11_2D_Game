#pragma once
#include "../Engine_SOURCE/MnBtNode.h"
#include "../Engine_SOURCE/MnBlackBoard.h"

namespace Mn
{
	class DestroyFish : public Node
	{
	public:
		DestroyFish();
		DestroyFish(BlackBoard* board);
		~DestroyFish();

		virtual enums::eBTState Run() override;
	private:
		BlackBoard* _BlackBoard;
	};

}
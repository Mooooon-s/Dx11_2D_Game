#pragma once
#include "MnBtNode.h"
#include "MnBlackBoard.h"
namespace Mn
{
	class Turn2Target : public Node
	{
	public:
		Turn2Target();
		Turn2Target(BlackBoard* board);
		~Turn2Target();

		enums::eBTState Run() override;
	public:
		void Turn2Fish();
		void Turn2Food();
	private:
		BlackBoard* _BlackBoard;
	};
}

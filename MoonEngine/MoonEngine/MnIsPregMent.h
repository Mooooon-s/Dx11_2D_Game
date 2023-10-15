#pragma once
#include "MnBtNode.h"
#include "MnBlackBoard.h"

namespace Mn
{
	class IsPregMent : public Node
	{
	public:
		IsPregMent();
		IsPregMent(BlackBoard* board);
		~IsPregMent();

		enums::eBTState Run() override;
	private:
		BlackBoard* _BlackBoard;
		float _Time;
		int _Flag;
	};
}

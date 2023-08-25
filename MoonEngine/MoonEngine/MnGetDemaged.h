#pragma once
#include "../Engine_SOURCE/MnBtNode.h"
#include "../Engine_SOURCE/MnBlackBoard.h"

namespace Mn
{
	class GetDemaged : public Node
	{
	public:
		GetDemaged();
		GetDemaged(BlackBoard* board);
		~GetDemaged();

		virtual enums::eBTState Run() override;
	private:
		BlackBoard* _BlackBoard;
	};

}